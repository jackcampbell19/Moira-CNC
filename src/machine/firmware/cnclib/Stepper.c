#include "Stepper.h"
#include <stdlib.h>


void stepper_construct(Stepper* stepper, int stp, int dir) {
    stepper->stp = stp;
    stepper->dir = dir;
}


/**
 * Rotates the stepper in the given direction.
 * direction == 0: no movement
 * direction == 1: move forward
 * direction == -1: move backwards
*/
void stepper_step(Stepper* stepper, int direction) {
    if (direction == 1) {
        // TODO: implement
    } else if (direction == -1) {
        // TODO: implement
    }
}