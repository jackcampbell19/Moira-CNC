#include <stdlib.h>
#include <string.h>
#include "SDCard.h"
#include "CNC.h"
#include "RotaryEncoder.h"
#include "Console.h"
#include "ConsoleScreen.h"
#include "ConsoleItem.h"


// Define variables
SDCard sd_card;
CNC cnc(0, 1, 2, 3, 4, 5);
RotaryEncoder rotenc(33, 34, 35);

void print_hi() {
  Serial.println("hi");
}
void print_hello() {
  Serial.println("hello");
}

char hn[16] = "Print Hi";
ConsoleItem printHi(hn, print_hi);
char hn2[16] = "P Hello";
ConsoleItem pH(hn2, print_hello);
// Add items
ConsoleScreen home;

Console console(13, 14, 15, 16, 17, 18, &home);

/**
 * Lifecycle: setup
 * Runs once upon board initilization.
*/
void setup() {
  // Open serial communications and wait for port to open
  Serial.begin(9600);
  while (!Serial) {}
  // Setup console screens
  home.addItem(&printHi);
  home.addItem(&pH);
  // Render initial screen
  console.render_screen();
}


/**
 * Lifecycle: loop
 * Continuiously executes this code block.
*/
void loop() {
  // Get the state of the rotary encoder
  int state = rotenc.get_state();
  // Check the state of the rotary encoder
  if (state == rotenc.BUTTON_PRESSED) {
    console.select();
  } else if (state == rotenc.ROTATE_LEFT) {
    console.up();
  } else if (state == rotenc.ROTATE_RIGHT) {
    console.down();
  }
  delay(1);
}


/**
 * Runs a '.mi' file from the sd card.
*/
void run_mi_file() {
  // Wait for the SD card to be inserted
  // display.message("Waiting for SD card...");
  while (!sd_card.is_inserted()) {};
  // Set the state and init SD card root
  // display.message("SD card detected.");
  sd_card.init_root();
  // Get the filename of the file to execute
  char filename[128];
  if (!sd_card.find_mi(filename)) {
    // If there is an error getting the filename
    // display.error("[ERROR] Failed to file '.mi' file on SD.");
    return;
  }
  // display.message("Found '.mi' file.");
  // Open the file
  if (!sd_card.open_mi(filename)) {
    // If the file cannot be opened
    // display.error("[ERROR] Could not open '.mi' file.");
    return;
  }
  // Read the instruction
  int bufsize = 64;
  char instruction[bufsize];
  while (sd_card.get_next_instruction(instruction, bufsize)) {
    // display.message(instruction);
    cnc.execute_instruction(instruction);
  }
  // Wait for for user.
  // display.message("Program ended, press button to reset");
}
