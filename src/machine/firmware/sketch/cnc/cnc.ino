#include "Hardware.h"
#include "RotaryEncoder.h"
#include "Screen.h"
#include "Actions.h"


Hardware hardware(13, 14, 15, 16, 17, 18, 33, 34, 35, 0, 1, 2, 3, 4, 5);


void addBackScreen(Screen* screen) {
	Screen* backScreen = new Screen("Back", back);
	screen->addSubScreen(backScreen);
}


void setup() {
	Serial.begin(9600);

	Screen* home = new Screen("Home", do_nothing);
		Screen* calibrate = new Screen("Calibrate", display_screen);
			addBackScreen(calibrate);
			Screen* moveX = new Screen("Move X", display_screen);
				addBackScreen(moveX);
				Screen* moveX500 = new Screen("500", move_x_500);
				moveX->addSubScreen(moveX500);
				Screen* moveX100 = new Screen("100", move_x_100);
				moveX->addSubScreen(moveX100);
				Screen* moveX10 = new Screen("10", move_x_10);
				moveX->addSubScreen(moveX10);
				Screen* moveX1 = new Screen("1", move_x_1);
				moveX->addSubScreen(moveX1);
			calibrate->addSubScreen(moveX);
			Screen* setOrigin = new Screen("Set Origin", set_origin);
			calibrate->addSubScreen(setOrigin);
		home->addSubScreen(calibrate);
		Screen* selectFile = new Screen("Select File", display_screen);
			addBackScreen(selectFile);
		home->addSubScreen(selectFile);
  
	hardware.setScreen(home);
	hardware.renderCurrentScreen();
}

void loop() {
	hardware.signal();
	delay(1);
}
