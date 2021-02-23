#include "CNC.h"
#include "../path/Sequence.h"
#include "../vector/Vector.h"
#include "Stepper.h"
#include <unistd.h>
#include "../ct/CoordinateTrace.h"


/**
 * Init the CNC device. Pulls specs from spesification file and sets up the various components.
*/
void cnc_init(CNC* cnc) {
    // Init specs for the machine
    specification_init(&cnc->specs);
    // Create the steppers
    stepper_construct(&cnc->X, cnc->specs.stepper_x_dir, cnc->specs.stepper_x_stp);
    stepper_construct(&cnc->Y, cnc->specs.stepper_y_dir, cnc->specs.stepper_y_stp);
    stepper_construct(&cnc->Z, cnc->specs.stepper_z_dir, cnc->specs.stepper_z_stp);
    // Init the stating position
    vector_construct(&cnc->current_position, 0, 0, 0);
}


/**
 * Sets the potition of the cnc to the given vector.
*/
void cnc_set_position(CNC* cnc, Vector* new_position) {
    if (vector_equals(&cnc->current_position, new_position)) {
        return;
    }
    Sequence sequence;
    sequence_generate(&sequence, &cnc->current_position, new_position);
    for (int i = 0; i < sequence.count; i++) {
        stepper_step(&cnc->X, (int) sequence.steps[i].x);
        stepper_step(&cnc->Y, (int) sequence.steps[i].y);
        stepper_step(&cnc->Z, (int) sequence.steps[i].z);
        usleep(8000);
    }
    vector_copy(&cnc->current_position, new_position);
}


void cnc_run_ct(CNC* cnc, char* path) {
    CoordinateTrace ct;
    ct_init(&ct, path);
    while (ct_nextline(&ct)) {
        // If the line contains a coordinate
        if (ct.line[0] == 'c') {
            int x;
            int y;
            int z;
            ct_parse_coord(&ct, &x, &y, &z);
            printf("Coord: %d, %d, %d\n", x, y, z);
        }
    }
    ct_close(&ct);
}