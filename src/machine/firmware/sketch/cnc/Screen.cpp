#include "Screen.h"
#include <string.h>


Screen::Screen(String title, void (*action)(Hardware*)) {
	strncpy(this->title, &title[0], 16);
	this->action = action;
}


void Screen::addSubScreen(Screen* subScreen) {
	this->subScreens[this->countSubScreens] = subScreen;
	++this->countSubScreens;
}
