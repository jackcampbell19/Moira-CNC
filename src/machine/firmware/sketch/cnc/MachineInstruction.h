#pragma once

#include "Hardware.h"

int parseWaitInstruction(char* instruction);
void parseCoordinateInstruction(char* instruction, Hardware* hardware, int* x, int* y, int* z);