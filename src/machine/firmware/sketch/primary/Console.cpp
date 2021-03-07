#include <Arduino.h>
#include "Console.h"
#include <String.h>
#include "CNC.h"


/**
 * Constructor for the Console.
*/
Console::Console(int rs, int e, int d4, int d5, int d6, int d7, CNC* cnc) : lcd(rs, e, d4, d5, d6, d7) {
  this->cnc = cnc;
  lcd.begin(16, 2);
	char str[16] = "Initilizing...";
	this->writeLine(str, 0);
}


/**
 * Sets the screen of the console and displays it to the LCD.
*/
void Console::setScreen(ConsoleScreen* s) {
  this->screen = s;
  this->renderScreen();
}


/**
 * Writes a line to the LCD in the given row.
*/
void Console::writeLine(char* str, int row) {
	this->lcd.setCursor(0, row);
	this->lcd.print(str);
}


/**
 * Instructs the screen selection to move up and then re-renders the screen.
*/
void Console::up() {
  if (this->screen->selection > 0) {
    --this->screen->selection;
    this->renderScreen();
  }
}


/**
 * Instructs the screen selection to move down and then re-renders the screen.
*/
void Console::down() {
  if (this->screen->selection < this->screen->count - 1) {
    ++this->screen->selection;
    this->renderScreen();
  }
}


/**
 * Calls the select function from from the selected ConsoleItem on the screen.
*/
void Console::select() {
  this->screen->items[this->screen->selection]->select_func();
  this->renderScreen();
}


/**
 * Clears the LCD screen.
*/
void Console::clear() {
  this->lcd.clear();
}


/**
 * Renders the current screen.
*/
void Console::renderScreen() {
	this->clear();
  char selected[16] = "> ";
  char not_selected[16] = "  ";
  if (this->screen->count == 1) {
    strcat(selected, this->screen->items[0]->name);
    this->writeLine(selected, 0);
  }
	if (this->screen->selection < this->screen->count - 1) {
    strcat(selected, this->screen->items[this->screen->selection]->name);
    strcat(not_selected, this->screen->items[this->screen->selection + 1]->name);
    this->writeLine(selected, 0);
    this->writeLine(not_selected, 1);
  }
  if (this->screen->selection == this->screen->count - 1) {
    strcat(selected, this->screen->items[this->screen->selection]->name);
    strcat(not_selected, this->screen->items[this->screen->selection - 1]->name);
    this->writeLine(not_selected, 0);
    this->writeLine(selected, 1);
  }
}


/**
 * Constructs a console item.
*/
ConsoleItem::ConsoleItem(char* n, void (*sf)()) {
	this->name = n;
	this->select_func = sf;
}

/**
 * Constructs a console screen.
*/
void ConsoleScreen::addItem(ConsoleItem* item) {
	this->items[this->count] = item;
	this->count += 1;
}


void initilize_console_screens(Console* console) {
//   ConsoleScreen* home = new ConsoleScreen();
//   char* calibrateTitle = new char [10];
//   strcpy(calibrateTitle, "Calibrate");
//   ConsoleItem* calibrate = new ConsoleItem(calibrateTitle, );

//   ConsoleScreen* calibrate = new ConsoleScreen();

}
