#include "ConsoleScreen.h"

void ConsoleScreen::addItem(ConsoleItem* item) {
	this->items[this->count] = item;
	this->count += 1;
}