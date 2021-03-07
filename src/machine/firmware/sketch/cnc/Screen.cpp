#include "Screen.h"
#include <string.h>


Screen::Screen(String title, void (*action)(Hardware*, Screen*)) {
	strncpy(this->title, &title[0], 16);
	this->action = action;
}


void Screen::addSubScreen(Screen* subScreen) {
	this->subScreens[this->countSubScreens] = subScreen;
	++this->countSubScreens;
  subScreen->superScreen = this;
}


void Screen::updateSelection(int i) {
	this->selection += i;
	if (this->selection < 0) {
		this->selection = 0;
	} else if (this->selection > this->countSubScreens - 1) {
		this->selection = this->countSubScreens - 1;
	}
}
