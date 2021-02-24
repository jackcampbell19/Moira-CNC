#include "CNC.h"
#include "../path/Sequence.h"
#include "../vector/Vector.h"
#include "Stepper.h"
#include <unistd.h>
#include "../mi/MachineInstruction.h"
#include <stdlib.h>
#include <string.h>
#include "../mi/Routine.h"


/**
 * Init the CNC device. Pulls specs from spesification file and sets up the various components.
*/
void cnc_init(CNC* cnc) {
    // Init specs for the machine
    specification_init(&cnc->specs);
    // Create the steppers
    stepper_construct(&cnc->X, cnc->specs.stepper_x_dir, cnc->specs.stepper_x_stp);
    stepper_construct(&cnc->Y, cnc->specs.stepper_y_dir, cnc->specs.stepper_y_stp);
    stepper_construct(&cnc->Z, cnc->specs.stepper_z_dir, cnc->specs.stepper_z_stp);
    // Init the stating position
    vector_construct(&cnc->current_position, 0, 0, 0);
}


/**
 * Sets the potition of the cnc to the given vector. Values cannot be negative.
*/
void cnc_set_position(CNC* cnc, Vector* new_position) {
    if (vector_equals(&cnc->current_position, new_position)) {
        return;
    }
    if (new_position->x < 0) {
        new_position->x = 0;
    }
    if (new_position->y < 0) {
        new_position->y = 0;
    }
    if (new_position->z < 0) {
        new_position->z = 0;
    }
    Sequence sequence;
    sequence_generate(&sequence, &cnc->current_position, new_position);
    for (int i = 0; i < sequence.count; i++) {
        stepper_step(&cnc->X, (int) sequence.steps[i].x);
        stepper_step(&cnc->Y, (int) sequence.steps[i].y);
        stepper_step(&cnc->Z, (int) sequence.steps[i].z);
        usleep(8000);
    }
    free(sequence.steps);
    vector_copy(&cnc->current_position, new_position);
}


/**
 * Executes the given instruction.
*/
void cnc_execute_instruction(CNC* cnc, MachineInstruction* mi, char* instruction) {

    // Execute 'Defined routine count' instruction
    if (instruction[0] == 'D') {
        mi_parse_defined_routine_count(mi, instruction);
        return;
    }

    // Execute 'routine definition' instruction
    if (instruction[0] == 'R') {
        int count;
        int id;
        mi_parse_define_routine(mi, instruction, &id, &count);
        for (size_t i = 0; i < count; i++) {
            mi_nextline(mi);
            // Store the lines from this routine
            mi_store_routine_instruction(mi, mi->line, id, i);
        }
        return;
    }

    // Execute 'routine' instruction
    if (instruction[0] == 'r') {
        int id;
        mi_parse_routine_instruction(mi, instruction, &id);
        for (size_t i = 0; i < mi->routines[id]->instruction_count; i++) {
            cnc_execute_instruction(cnc, mi, mi->routines[id]->instructions[i]);
        }
        return;
    }

    // Execute 'coordinate' instruction
    if (instruction[0] == 'c') {
        Vector coordinate;
        mi_parse_coord(mi, cnc, instruction, &coordinate);
        vector_print(&coordinate); // REMOVE
        cnc_set_position(cnc, &coordinate);
        return;
    }

    // Execute 'wait' instruction
    if (instruction[0] == 'w') {
        int milliseconds;
        mi_parse_wait_instruction(mi, instruction, &milliseconds);
        usleep(milliseconds);
        return;
    }

    // Execute 'special' instruction
    if (instruction[0] == 's') {
        // TODO: implement
        return;
    }
}


/**
 * Runs a '.mi' file.
 * @param cnc the CNC
 * @param path the path to the '.mi' file
*/
void cnc_run_mi(CNC* cnc, char* path) {
    // Create the mi struct
    MachineInstruction mi;
    mi_init(&mi, path);
    // Iterate over each instruction line
    while (mi_nextline(&mi)) {
        // Skip the line if it is blank
        if (strlen(mi.line) <= 1) {
            continue;
        }
        // Execute the instruction
        cnc_execute_instruction(cnc, &mi, mi.line);
    }
    // Close out the mi file
    mi_close(&mi);
}