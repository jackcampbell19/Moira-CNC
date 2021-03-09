#include "Hardware.h"
#include "RotaryEncoder.h"
#include "Screen.h"
#include "Actions.h"


Hardware hardware(13, 14, 15, 16, 17, 18, 33, 34, 35, 0, 1, 2, 3, 4, 5);


void addBackScreen(Screen* screen) {
	Screen* backScreen = new Screen("Back", back);
	screen->addSubScreen(backScreen);
}


/**
 * Lifecycle: setup
 * Runs once upon initilization, sets up the screens.
*/
void setup() {

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
			Screen* moveY = new Screen("Move Y", display_screen);
				addBackScreen(moveY);
				Screen* moveY500 = new Screen("500", move_y_500);
				moveY->addSubScreen(moveY500);
				Screen* moveY100 = new Screen("100", move_y_100);
				moveY->addSubScreen(moveY100);
				Screen* moveY10 = new Screen("10", move_y_10);
				moveY->addSubScreen(moveY10);
				Screen* moveY1 = new Screen("1", move_y_1);
				moveY->addSubScreen(moveY1);
			calibrate->addSubScreen(moveY);
			Screen* moveZ = new Screen("Move Z", display_screen);
				addBackScreen(moveZ);
				Screen* moveZ500 = new Screen("500", move_z_500);
				moveZ->addSubScreen(moveZ500);
				Screen* moveZ100 = new Screen("100", move_z_100);
				moveZ->addSubScreen(moveZ100);
				Screen* moveZ10 = new Screen("10", move_z_10);
				moveZ->addSubScreen(moveZ10);
				Screen* moveZ1 = new Screen("1", move_z_1);
				moveZ->addSubScreen(moveZ1);
			calibrate->addSubScreen(moveZ);
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
