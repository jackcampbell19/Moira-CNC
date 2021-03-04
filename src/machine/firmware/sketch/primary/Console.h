#pragma once

#include <LiquidCrystal.h>
#include "ConsoleScreen.h"


class Console {

	public:

	Console(int rs, int e, int d4, int d5, int d6, int d7, ConsoleScreen* init_screen);
	void display(char* str, int row);
	void render_screen();
  	void up();
  	void down();
  	void select();

	private:

	LiquidCrystal lcd;
	ConsoleScreen* screen;

};
