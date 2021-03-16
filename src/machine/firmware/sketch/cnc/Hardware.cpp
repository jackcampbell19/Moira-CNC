#include "Hardware.h"
#include <string.h>
#include "MachineInstruction.h"


Hardware::Hardware(int lcd_rs, int lcd_e, int lcd_d4, int lcd_d5, int lcd_d6, int lcd_d7, 
					int re_clk, int re_dt, int re_sw, 
					int x_stp, int x_dir, int y_stp, int y_dir, int z_stp, int z_dir) : 
						lcd(lcd_rs, lcd_e, lcd_d4, lcd_d5, lcd_d6, lcd_d7), 
						rotaryEncoder(re_clk, re_dt, re_sw), 
						x(x_stp, x_dir), 
						y(y_stp, y_dir), 
						z(z_stp, z_dir) {
	this->lcd.begin(16, 2);
}


void Hardware::renderCurrentScreen() {
	this->lcd.clear();
  char selected[16] = "> ";
  char not_selected[16] = "  ";
  if (this->currentScreen->countSubScreens == 1) {
    strcat(selected, this->currentScreen->subScreens[0]->title);
	this->lcd.setCursor(0, 0);
    this->lcd.print(selected);
	return;
  }
  if (this->currentScreen->selection < this->currentScreen->countSubScreens - 1) {
    strcat(selected, this->currentScreen->subScreens[this->currentScreen->selection]->title);
    strcat(not_selected, this->currentScreen->subScreens[this->currentScreen->selection + 1]->title);
    this->lcd.setCursor(0, 0);
    this->lcd.print(selected);
    this->lcd.setCursor(0, 1);
    this->lcd.print(not_selected);
  }
  if (this->currentScreen->selection == this->currentScreen->countSubScreens - 1) {
    strcat(selected, this->currentScreen->subScreens[this->currentScreen->selection]->title);
    strcat(not_selected, this->currentScreen->subScreens[this->currentScreen->selection - 1]->title);
    this->lcd.setCursor(0, 0);
    this->lcd.print(not_selected);
    this->lcd.setCursor(0, 1);
    this->lcd.print(selected);
  }
}


void Hardware::setScreen(Screen* screen) {
	this->currentScreen = screen;
}


void Hardware::setPosition(int x, int y, int z) {
  this->x.setTargetAbs(x);
  this->y.setTargetAbs(y);
  this->z.setTargetAbs(z);
  this->controller.moveAsync(this->x, this->y, this->z);
  while (this->controller.isRunning()) {
    delay(10);
  }
}


void Hardware::executeInstruction(char* instruction) {
	// Execute 'coordinate' instruction
    if (instruction[0] == 'c') {
        int x;
        int y;
        int z;
        parseCoordinateInstruction(instruction, this, &x, &y, &z);
        this->setPosition(x, y, z);
        return;
    }
    // Execute 'wait' instruction
    if (instruction[0] == 'w') {
        int milliseconds = parseWaitInstruction(instruction);
        delay(milliseconds);
        return;
    }
    // Execute 'special' instruction
    if (instruction[0] == 's') {
        // TODO: implement
        return;
    }
}


void Hardware::signal() {
  RotaryEncoderState state = this->rotaryEncoder.getState();
  if (state == CW) {
    this->currentScreen->updateSelection(1);
  } else if (state == CCW) {
    this->currentScreen->updateSelection(-1);
  } else if (state == BP) {
    Screen* s = this->currentScreen->subScreens[this->currentScreen->selection];
    s->action(this, s);
  } else if (state == NONE) {
    return;
  }
  this->renderCurrentScreen();
}
