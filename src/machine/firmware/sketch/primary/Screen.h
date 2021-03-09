#pragma once

#include "CNC.h"


class Screen {

	public:

		char title[16]; // The title of the screen
		size_t countSubScreens = 0; // The number of subscreens
		Screen* subScreens[64]; // The array of subscreen pointers, max of 64 subscreens per screen
		int selection = 0; // The current selection on the screen


		/**
		 * Adds a subscreen to the screen.
		 */
		void addSubScreen(Screen* subScreen) {
			this->subScreens[this.countSubScreens] = subScreen;
			++this.countSubScreens;
		}


		/**
		 * A payload function to be executed whe this screen is clicked on from a superscreen.
		 */
		virtual void payload(CNC* cnc) {}

}


class Home : public Screen {
	public:
		char title[16] = "Home";

		void payload(CNC* cnc) override {
			
		}
		
}