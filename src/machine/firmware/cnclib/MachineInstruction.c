#include "MachineInstruction.h"
#include <string.h>
#include "Vector.h"
#include <stdlib.h>


/**
 * Parses a 'coordinate' instruction.
*/
void mi_parse_coordinate(char* instruction, Vector* current, Vector* coordinate) {
    char *raw_str;
    // Advance the string past the instruction type and tokenize with comma
    raw_str = strtok(&instruction[2], ",");
    // Check x for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->x = current->x + atoi(raw_str);
    } else {
        // Else set x to x value
        coordinate->x = atoi(raw_str);
    }
    raw_str = strtok(NULL, ",");
    // Check y for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->y = current->y + atoi(raw_str);
    } else {
        // Else set y to y value
        coordinate->y = atoi(raw_str);
    }
    raw_str = strtok(NULL, ",");
    // Check y for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->z = current->z + atoi(raw_str);
    } else {
        // Else set y to y value
        coordinate->z = atoi(raw_str);
    }
}


/**
 * Parses a 'wait' instruction.
*/
void mi_parse_wait_instruction(char* instruction, int* milliseconds) {
    // Parse instruction
    *milliseconds = atoi(&instruction[2]);
}
