#pragma once

/**
  * The state during runtime.
  */
class State {

  public:

  // Possible states
  const int WAITING_FOR_SD = 0;
  const int SD_INSERTED = 1;
  const int MI_FILE_EXECUTING = 2;
  const int ERROR = 3;
  const int INIT = 4;

  // Current state
  int current_state;

  // Methods
  State();
  void set(int new_state);
  
};
