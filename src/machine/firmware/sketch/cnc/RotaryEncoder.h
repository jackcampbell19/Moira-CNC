#pragma once

/**
 * Possible states of the rotaryEncoder, clockwise, counter clockwise, button press, and none
*/
enum RotaryEncoderState { CW = 0, CCW = 1, BP = 2, NONE = 3 };


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
  RotaryEncoderState getState();
  
};
