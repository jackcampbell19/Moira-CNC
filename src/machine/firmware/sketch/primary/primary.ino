#include <stdlib.h>
#include <string.h>
#include "SDCard.h"
#include "CNC.h"
#include "RotaryEncoder.h"
#include "Console.h"


size_t stmax(size_t a, size_t b) {
  if (a > b) {
    return a;
  }
  return b;
}

size_t stmin(size_t a, size_t b) {
  if (a < b) {
    return a;
  }
  return b;
}


///////////////////////////////////////////////////////////////////////////
//////   Objects defined here are avaliable globally. All objects    //////
//////   initilized with gpio pins must be defined here.             //////
///////////////////////////////////////////////////////////////////////////
SDCard sdCard;
CNC cnc(0, 1, 2, 3, 4, 5);
RotaryEncoder dial(33, 34, 35);
Console console(13, 14, 15, 16, 17, 18, &cnc);
///////////////////////////////////////////////////////////////////////////



/**
 * Lifecycle: setup
 * Runs once upon board initilization.
*/
void setup() {
}


/**
 * Lifecycle: loop
 * Continuiously executes this code block.
*/
void loop() {
  // Get the state of the rotary encoder
  int state = dial.getState();
  // Check the state of the rotary encoder
  if (state == dial.BUTTON_PRESSED) {
    console.select();
  } else if (state == dial.ROTATE_LEFT) {
    console.up();
  } else if (state == dial.ROTATE_RIGHT) {
    console.down();
  }
  delay(1);
}
