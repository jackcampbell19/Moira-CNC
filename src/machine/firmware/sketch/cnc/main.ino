#include "Hardware.h"
#include "RotaryEncoder.h"
#include "Screen.h"
#include "Actions.h"


Hardware hardware(13, 14, 15, 16, 17, 18, 33, 34, 35, 0, 1, 2, 3, 4, 5);


void setup() {
	Serial.begin(9600);
	Screen* home = new Screen("Home", do_nothing);
	Screen* calibrate = new Screen("Calibrate", do_nothing);
	Screen* selectFile = new Screen("Select File", do_nothing);
	home->addSubScreen(calibrate);
	home->addSubScreen(selectFile);
	hardware.setScreen(home);
}

void loop() {
	switch (hardware.rotaryEncoder.getState()) {
	case CW:
		Serial.println("Clockwise");
		break;
	case CCW:
		Serial.println("Counter Clockwise");
		break;
	case BP:
		Serial.println("Button Pressed");
		break;
	default:
		break;
	}
	delay(1);
}
