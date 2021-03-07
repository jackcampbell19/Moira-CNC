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
RotaryEncoderState RotaryEncoder::getState() {
  RotaryEncoderState state = NONE;
  this->clk_current = digitalRead(this->clk);
  if (this->clk_current != this->clk_last && this->clk_current == 1) {
    if (digitalRead(this->dt) != this->clk_current) {
      state = CW;
    } else {
      state = CCW;
    }
  }
  this->clk_last = this->clk_current;
  int btn_state = digitalRead(this->sw);
  if (btn_state == LOW) {
    if (millis() - this->last_button_press > 50) {
      state = BP;
    }
    this->last_button_press = millis();
  }
  return state;
}
