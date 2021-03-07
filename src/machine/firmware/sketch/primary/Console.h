#pragma once

#include <LiquidCrystal.h>
#include "CNC.h"

/**
 * ConsoleItem is an object that is displayed on a ConsoleScreen. Each item also contains a 
 * function pointer that is called when the item is selected.
*/
class ConsoleItem {

  public:

  char* name; // Name of the item
  void (*select_func)(); // Function to envoke when item is selected
  ConsoleItem(char* n, void (*sf)());


};


/**
 * ConsoleScreen is an object that holds a list of items to display.
*/
class ConsoleScreen {

  public:

  int count = 0; // Actual number of items
  ConsoleItem* items[8]; // Maximum of 8 items per screen
  ConsoleScreen() = default;
  void addItem(ConsoleItem* item);

  int selection = 0;

};


/**
 * Console is an object that controls the LCD screen and dispatches actions based on user input.
*/
class Console {

	public:

	Console(int rs, int e, int d4, int d5, int d6, int d7, CNC* cnc);
	void writeLine(char* str, int row);
	void renderScreen();
  	void up();
  	void down();
  	void select();
	void setScreen(ConsoleScreen* s);
    void clear();

	private:

	LiquidCrystal lcd;
	CNC* cnc;
	ConsoleScreen* screen;

};


/**
 * Creates the console screens and adds them to the console.
*/
void initilize_console_screens(Console* console);
