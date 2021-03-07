#include "Actions.h"
#include <string.h>

void do_nothing(Hardware* hardware, Screen* screen) {}

void back(Hardware* hardware, Screen* screen) {
  hardware->setScreen(screen->superScreen->superScreen);
}

void display_screen(Hardware* hardware, Screen* screen) {
  hardware->setScreen(screen);
}

void set_origin(Hardware* hardware, Screen* screen) {
	hardware->x.setPosition(0);
	hardware->y.setPosition(0);
	hardware->z.setPosition(0);
	hardware->lcd.clear();
	hardware->lcd.setCursor(0, 0);
	hardware->lcd.print("Origin Set");
	delay(1000);
}

void helper_display_current_position(Hardware* hardware) {
    hardware->lcd.clear();
    hardware->lcd.setCursor(0, 0);
    char str[16];
    snprintf(str, 15, "%d/%d/%d", (int) hardware->x.getPosition(), (int) hardware->y.getPosition(), (int) hardware->z.getPosition());
    hardware->lcd.print(str);
}

void helper_move_axis(Stepper* stepper, Hardware* hardware, int steps) {
  helper_display_current_position(hardware);
	while (1) {
		int s = 0;
		RotaryEncoderState state = hardware->rotaryEncoder.getState();
  		if (state == CW) {
    		s = steps;
  		} else if (state == CCW) {
    		s = -steps;
  		} else if (state == BP) {
    		return;
  		} else if (state == NONE) {
			  delay(1);
    		continue;
  		}
		stepper->setTargetRel(s);
		hardware->controller.move(*stepper);
		while (hardware->controller.isRunning()) {
			delay(10);
		}
    helper_display_current_position(hardware);
		delay(1);
	}
}

void move_x_500(Hardware* hardware, Screen* screen) {
	helper_move_axis(&hardware->x, hardware, 500);
}

void move_x_100(Hardware* hardware, Screen* screen) {
	helper_move_axis(&hardware->x, hardware, 100);
}

void move_x_10(Hardware* hardware, Screen* screen) {
	helper_move_axis(&hardware->x, hardware, 10);
}

void move_x_1(Hardware* hardware, Screen* screen) {
	helper_move_axis(&hardware->x, hardware, 1);
}
