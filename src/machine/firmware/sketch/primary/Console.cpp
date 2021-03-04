#include "Console.h"
#include <Arduino.h>
#include <String.h>


Console::Console(int rs, int e, int d4, int d5, int d6, int d7, ConsoleScreen* init_screen) : lcd(rs, e, d4, d5, d6, d7) {
  lcd.begin(16, 2);
	char str[16] = "Initilizing...";
	this->display(str, 0);
	this->screen = init_screen;
}


void Console::display(char* str, int row) {
	this->lcd.setCursor(0, row);
	this->lcd.print(str);
}


void Console::up() {
  if (this->screen->selection > 0) {
    --this->screen->selection;
    this->render_screen();
  }
}


void Console::down() {
  if (this->screen->selection < this->screen->count - 1) {
    ++this->screen->selection;
    this->render_screen();
  }
}


void Console::select() {
  this->screen->items[this->screen->selection]->select_func();
  this->render_screen();
}


void Console::render_screen() {
	this->lcd.clear();
  char selected[16] = "> ";
  char not_selected[16] = "  ";
  if (this->screen->count == 1) {
    strcat(selected, this->screen->items[0]->name);
    this->display(selected, 0);
  }
	if (this->screen->selection < this->screen->count - 1) {
    strcat(selected, this->screen->items[this->screen->selection]->name);
    strcat(not_selected, this->screen->items[this->screen->selection + 1]->name);
    this->display(selected, 0);
    this->display(not_selected, 1);
  }
  if (this->screen->selection == this->screen->count - 1) {
    strcat(selected, this->screen->items[this->screen->selection]->name);
    strcat(not_selected, this->screen->items[this->screen->selection - 1]->name);
    this->display(not_selected, 0);
    this->display(selected, 1);
  }
  
}
