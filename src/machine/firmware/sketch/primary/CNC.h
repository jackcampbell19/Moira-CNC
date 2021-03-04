#pragma once

#include "TeensyStep.h"
#include "Coordinate.h"

class CNC {

	public:

	CNC(int x_stp, int x_dir, int y_stp, int y_dir, int z_stp, int z_dir);
	void execute_instruction(char* instruction);
	void set_position(Coordinate coordinate);
	int parse_wait_instruction(char* instruction);
	void parse_coordinate_instruction(char* instruction, Coordinate* coordinate);

	private:

	StepControl controller;
	Stepper x;
	Stepper y;
	Stepper z;

};
