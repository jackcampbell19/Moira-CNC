#pragma once

#include <LiquidCrystal.h>
#include "TeensyStep.h"
#include "RotaryEncoder.h"
#include "Screen.h"
#include "SDCard.h"

/**
 * Initilizes the hardware and allows for communication to it
*/
class Hardware {

	public:

		LiquidCrystal lcd;
		RotaryEncoder rotaryEncoder;
		Stepper x;
		Stepper y;
		Stepper z;
		StepControl controller;
		SDCard sd;
		
		Screen* currentScreen;

		// Constructs the hardware class
		Hardware(int lcd_rs, int lcd_e, int lcd_d4, int lcd_d5, int lcd_d6, int lcd_d7, 
					int re_clk, int re_dt, int re_sw, 
					int x_stp, int x_dir, int y_stp, int y_dir, int z_stp, int z_dir);

		// Renders the current screen
		void renderCurrentScreen();

		// Sets the current screen
		void setScreen(Screen* screen);

		// Sets the steppers to tne given positions
		void setPosition(int x, int y, int z);

		void executeInstruction(char* instruction);

		void signal();

};
