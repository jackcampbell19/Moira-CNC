#pragma once

class RotaryEncoder {

  private:

  int clk;
  int dt;
  int sw;
  int clk_last;
  int clk_current;
  unsigned long last_button_press;

  public:

  RotaryEncoder(int clk, int dt, int sw);
  int get_state();

  int ROTATE_RIGHT = 0b001;
  int ROTATE_LEFT = 0b010;
  int BUTTON_PRESSED = 0b100;
  
};