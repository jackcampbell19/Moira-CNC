#include <stdlib.h>
#include <string.h>
#include "State.h"
#include "SDCard.h"
#include "MachineLog.h"


// Define variables
MachineLog mlog;
State state;
SDCard sd_card;


/**
 * Lifecycle: setup
 * Runs once upon board initilization.
*/
void setup() {
  // Set the state
  state.set(state.INIT);
  // Open serial communications and wait for port to open
  Serial.begin(9600);
  while (!Serial) {}
}


/**
 * Lifecycle: loop
 * Continuiously executes this code block.
*/
void loop() {
  // Set the state and wait for the SD card to be inserted
  mlog.write("Waiting for SD card...");
  state.set(state.WAITING_FOR_SD);
  while (!sd_card.is_inserted()) {};
  // Set the state and init SD card root
  mlog.write("SD card detected.");
  state.set(state.SD_INSERTED);
  sd_card.init_root();
  // Get the filename of the file to execute
  char filename[128];
  if (!sd_card.find_mi(filename)) {
    // If there is an error getting the filename
    mlog.write("[ERROR] Failed to file '.mi' file on SD.");
    state.set(state.ERROR);
    wait_for_reset();
    return;
  }
  mlog.write("Found '.mi' file.");
  mlog.write(filename);
  // Open the file
  if (!sd_card.open_mi(filename)) {
    // If the file cannot be opened
    mlog.write("[ERROR] Could not open '.mi' file.");
    state.set(state.ERROR);
    wait_for_reset();
    return;
  }
  // Read the instruction
  int bufsize = 64;
  char instruction[bufsize];
  while (sd_card.get_next_instruction(instruction, bufsize)) {
    mlog.write(instruction);
  }
  // Wait for for user.
  mlog.write("Program ended, waiting for user to reset.");
  wait_for_reset();
}


/**
 * Waits for the user to reset.
*/
void wait_for_reset() {
  while (true) {};
}