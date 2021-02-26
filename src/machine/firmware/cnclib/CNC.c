#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "CNC.h"
#include "MachineInstruction.h"
#include "Stepper.h"
#include "Vector.h"


/**
 * Calculates sequence of steps to take to draw a line with a given x, y, z coordinates from s to e.
*/
Vector* sequence_generate(Vector* s, Vector* e, int* count) {
    *count = 0;
    Vector d;
    vector_subtract(e, s, &d);
    double m = round(vector_norm(&d));
    if (m == 0) {
        return 0;
    }
    double f = 1.0 / m;
    Vector last_position;
    vector_zero(&last_position);
    double scalar = 0;
    Vector* sequence = (Vector*) malloc(sizeof(Vector) * (m + 1));
    Vector vector_position;
    Vector dv;
    for (size_t i = 0; i <= (size_t) m; i++) {
        vector_multiply(&d, scalar, &vector_position);
        vector_round_t(&vector_position);
        vector_subtract(&vector_position, &last_position, &dv);
        if (vector_norm(&dv) > 0) {
            vector_floor_t(&dv);
            vector_copy(&sequence[*count], &dv);
            *count = *count + 1;
        }
        vector_copy(&last_position, &vector_position);
        scalar += f;
    }
    return sequence;
}


/**
 * Init the CNC device. Pulls specs from spesification file and sets up the various components.
*/
void cnc_init(CNC* cnc, int x_dir, int x_stp, int y_dir, int y_stp, int z_dir, int z_stp) {
    // Create the steppers
    stepper_construct(&cnc->X, x_dir, x_stp);
    stepper_construct(&cnc->Y, y_dir, y_stp);
    stepper_construct(&cnc->Z, z_dir, z_stp);
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
    int count;
    Vector* sequence = sequence_generate(&cnc->current_position, new_position, &count);
    for (int i = 0; i < count; i++) {
        stepper_step(&cnc->X, (int) sequence[i].x);
        stepper_step(&cnc->Y, (int) sequence[i].y);
        stepper_step(&cnc->Z, (int) sequence[i].z);
        usleep(8000);
    }
    free(sequence);
    vector_copy(&cnc->current_position, new_position);
}


/**
 * Executes the given instruction.
 * @param cnc the cnc device
 * @param instruction the string instruction to execute
*/
void cnc_execute_instruction(CNC* cnc, char* instruction) {
    // Execute 'coordinate' instruction
    if (instruction[0] == 'c') {
        Vector coordinate;
        mi_parse_coordinate(instruction, &cnc->current_position, &coordinate);
        vector_print(&coordinate); // REMOVE
        cnc_set_position(cnc, &coordinate);
        return;
    }
    // Execute 'wait' instruction
    if (instruction[0] == 'w') {
        int milliseconds;
        mi_parse_wait_instruction(instruction, &milliseconds);
        usleep(milliseconds);
        return;
    }
    // Execute 'special' instruction
    if (instruction[0] == 's') {
        // TODO: implement
        return;
    }
}
