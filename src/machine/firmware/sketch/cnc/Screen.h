#pragma once

#include <Arduino.h>

class Hardware; // Promise that this class exists without defining it

class Screen {

	public:

		char title[16]; // The title of the screen
		int countSubScreens = 0; // The number of subscreens
		Screen* subScreens[16]; // The array of subscreen pointers, max of 16 subscreens per screen
		int selection = 0; // The current selection on the screen
		void (*action)(Hardware*); // A function to execute when the screen is selected from a superscreen


		Screen(String title, void (*action)(Hardware*));
		void addSubScreen(Screen* subScreen);

};
