#include "MachineInstruction.h"
#include <stdlib.h>
#include <string.h>


int parseWaitInstruction(char* instruction) {
	return (int) atoi(&instruction[2]);
}


void parseCoordinateInstruction(char* instruction, Hardware* hardware, int* x, int* y, int* z) {
	char *raw_str;
    // Advance the string past the instruction type and tokenize with comma
    raw_str = strtok(&instruction[2], ",");
    // Check x for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        *x = hardware->x.getPosition() + atoi(raw_str);
    } else {
        // Else set x to x value
        *x = atoi(raw_str);
    }
    raw_str = strtok(NULL, ",");
    // Check y for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        *y = hardware->y.getPosition() + atoi(raw_str);
    } else {
        // Else set y to y value
        *y = atoi(raw_str);
    }
    raw_str = strtok(NULL, ",");
    // Check y for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        *z = hardware->z.getPosition() + atoi(raw_str);
    } else {
        // Else set y to y value
        *z = atoi(raw_str);
    }
}