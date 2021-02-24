#include "MachineInstruction.h"
#include <string.h>
#include "../hardware/CNC.h"
#include "../vector/Vector.h"
#include "Routine.h"

void mi_init(MachineInstruction* mi, char* path) {
    mi->path = path;
    mi->fp = fopen(path, "r");
    if (mi->fp == NULL)
        exit(EXIT_FAILURE);
    mi->len = 128;
    mi->line = (char *) malloc(sizeof(char) * mi->len + 1);
    mi->defined_routine_count = 0;
}

int mi_nextline(MachineInstruction* mi) {
    return fgets(mi->line, mi->len, mi->fp) != NULL;
}

void mi_close(MachineInstruction* mi) {
    fclose(mi->fp);
    free(mi->line);
    for (size_t i = 0; i < mi->defined_routine_count; i++) {
        free(mi->routines[i]);
    }
    free(mi->routines);
}

/**
 * Parses a type 'c' instruction returning the values of x, y, and z.
*/
void mi_parse_coord(MachineInstruction* mi, CNC* cnc, char* instruction, Vector* coordinate) {
    char *raw_str;
    // Advance the string past the instruction type and tokenize with comma
    raw_str = strtok(&instruction[2], ",");
    // Check x for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->x = cnc->current_position.x + atoi(raw_str);
    } else {
        // Else set x to x value
        coordinate->x = atoi(raw_str);
    }
    raw_str = strtok(NULL, ",");
    // Check y for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->y = cnc->current_position.y + atoi(raw_str);
    } else {
        // Else set y to y value
        coordinate->y = atoi(raw_str);
    }
    raw_str = strtok(NULL, ",");
    // Check y for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->z = cnc->current_position.z + atoi(raw_str);
    } else {
        // Else set y to y value
        coordinate->z = atoi(raw_str);
    }
}

/**
 * Parses a defined routine count instruction. Mallocs the routines field of the mi.
*/
void mi_parse_defined_routine_count(MachineInstruction* mi, char* instruction) {
    // Parse the instruction
    mi->defined_routine_count = atoi(&instruction[2]);
    // malloc the list of routine pointers
    mi->routines = (Routine**) malloc(sizeof(Routine*) * mi->defined_routine_count);
}

/**
 * Parses a 'routine definition' instruction. Mallocs the routine for the given id and stores the routine id and count in the vars.
*/
void mi_parse_define_routine(MachineInstruction* mi, char* instruction, int* id, int* count) {
    // Parse the instruction
    char* raw_str;
    raw_str = strtok(&instruction[2], ":");
    *id = atoi(raw_str);
    raw_str = strtok(NULL, ":");
    *count = atoi(raw_str);
    // malloc routine
    mi->routines[*id] = (Routine*) malloc(sizeof(Routine));
    // Set instruction count
    mi->routines[*id]->instruction_count = *count;
    // malloc the list of instruction pointers
    mi->routines[*id]->instructions = (char**) malloc(sizeof(char*) * (*count));
}

/**
 * Stores an 'instruction' at 'index' in the routine with matching 'id'.
*/
void mi_store_routine_instruction(MachineInstruction* mi, char* instruction, int id, int index) {
    // malloc the routine instruction
    mi->routines[id]->instructions[index] = (char*) malloc(sizeof(char) * (strlen(instruction) + 1));
    // Copy the instruction into the routine
    strcpy(mi->routines[id]->instructions[index], instruction);
}

/**
 * Parses a 'routine' instruction. Returns the routine in the params.
*/
void mi_parse_routine_instruction(MachineInstruction* mi, char* instruction, int* id) {
    // Parse instruction
    *id = atoi(&instruction[2]);
}

/**
 * Parses a 'wait' instruction.
*/
void mi_parse_wait_instruction(MachineInstruction* mi, char* instruction, int* milliseconds) {
    // Parse instruction
    *milliseconds = atoi(&instruction[2]);
}