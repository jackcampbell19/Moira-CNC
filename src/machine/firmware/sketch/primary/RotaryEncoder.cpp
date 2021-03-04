#include <Arduino.h>
#include "RotaryEncoder.h"


RotaryEncoder::RotaryEncoder(int clk, int dt, int sw) {
  this->clk = clk;
  this->dt = dt;
  this->sw = sw;
  pinMode(clk,INPUT);
  pinMode(dt,INPUT);
  pinMode(sw, INPUT_PULLUP);
  this->clk_last = digitalRead(clk);
  this->last_button_press = 0;
}


/**
 * Gets the current state of the rotary encoder.
 */
int RotaryEncoder::get_state() {
  int value = 0;
  this->clk_current = digitalRead(this->clk);
  if (this->clk_current != this->clk_last  && this->clk_current == 1) {
    if (digitalRead(this->dt) != this->clk_current) {
      value = this->ROTATE_RIGHT;
    } else {
      value = this->ROTATE_LEFT;
    }
  }
  this->clk_last = this->clk_current;
  int btn_state = digitalRead(this->sw);
  if (btn_state == LOW) {
    if (millis() - this->last_button_press > 50) {
      value = this->BUTTON_PRESSED;
    }
    this->last_button_press = millis();
  }
  return value;
}