#include "ConsoleItem.h"

ConsoleItem::ConsoleItem(char* n, void (*sf)()) {
	this->name = n;
	this->select_func = sf;
}