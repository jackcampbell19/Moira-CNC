#pragma once

class ConsoleItem {

	public:

	char* name; // Name of the item
	void (*select_func)(); // Function to envoke when item is selected
	ConsoleItem(char* n, void (*sf)());


};