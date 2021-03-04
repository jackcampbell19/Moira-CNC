#pragma once

#include "ConsoleItem.h"

class ConsoleScreen {

	public:

	int count = 0; // Actual number of items
	ConsoleItem* items[8]; // Maximum of 8 items per screen
	ConsoleScreen() = default;
	void addItem(ConsoleItem* item);

	int selection = 0;

};
