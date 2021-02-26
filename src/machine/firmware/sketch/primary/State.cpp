#include "State.h"

/**
 * Sets the state.
*/
State::State() {
  this->current_state = this->INIT;
}


/**
 * Sets the state.
*/
void State::set(int new_state) {
  this->current_state = new_state;
}
