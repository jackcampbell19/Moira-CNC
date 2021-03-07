#pragma once

#include "TeensyStep.h"
#include "Coordinate.h"

class CNC {

	public:

	CNC(int x_stp, int x_dir, int y_stp, int y_dir, int z_stp, int z_dir);
	void executeInstruction(char* instruction);
	void setPosition(Coordinate coordinate);
	int parseWaitInstruction(char* instruction);
	void parseCoordinateInstruction(char* instruction, Coordinate* coordinate);
	void setOrigin();
	int getXpos();
	int getYpos();
	int getZpos();

	private:

	StepControl controller;
	Stepper x;
	Stepper y;
	Stepper z;

};
