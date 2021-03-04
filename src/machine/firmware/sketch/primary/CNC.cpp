#include "CNC.h"
#include "TeensyStep.h"
#include "Coordinate.h"
#include <Arduino.h>


CNC::CNC(int x_stp, int x_dir, int y_stp, int y_dir, int z_stp, int z_dir) : x(x_stp, x_dir), y(y_stp, y_dir), z(z_stp, z_dir) {}


void CNC::execute_instruction(char* instruction) {
	// Execute 'coordinate' instruction
    if (instruction[0] == 'c') {
        Coordinate coordinate;
        this->parse_coordinate_instruction(instruction, &coordinate);
        this->set_position(coordinate);
        return;
    }
    // Execute 'wait' instruction
    if (instruction[0] == 'w') {
        int milliseconds = this->parse_wait_instruction(instruction);
        delay(milliseconds);
        return;
    }
    // Execute 'special' instruction
    if (instruction[0] == 's') {
        // TODO: implement
        return;
    }
}


/**
 * Rotates the motors to the given positions syncronously, returns when motors have stopped.
*/
void CNC::set_position(Coordinate coordinate) {
	this->x.setTargetAbs(coordinate.x);
	this->y.setTargetAbs(coordinate.y);
	this->z.setTargetAbs(coordinate.z);
	this->controller.moveAsync(this->x, this->y, this->z);
	while (this->controller.isRunning()) {
		delay(10);
	}
}


int CNC::parse_wait_instruction(char* instruction) {
    return (int) atoi(&instruction[2]);
}

void CNC::parse_coordinate_instruction(char* instruction, Coordinate* coordinate) {
    char *raw_str;
    // Advance the string past the instruction type and tokenize with comma
    raw_str = strtok(&instruction[2], ",");
    // Check x for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->x = this->x.getPosition() + atoi(raw_str);
    } else {
        // Else set x to x value
        coordinate->x = atoi(raw_str);
    }
    raw_str = strtok(NULL, ",");
    // Check y for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->y = this->y.getPosition() + atoi(raw_str);
    } else {
        // Else set y to y value
        coordinate->y = atoi(raw_str);
    }
    raw_str = strtok(NULL, ",");
    // Check y for prepended value
    if (raw_str[0] == '+' || raw_str[0] == '-') {
        // Add/subtract x value to current x value
        coordinate->z = this->z.getPosition() + atoi(raw_str);
    } else {
        // Else set y to y value
        coordinate->z = atoi(raw_str);
    }
}
