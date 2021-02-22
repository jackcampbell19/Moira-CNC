#include "Specification.h"

void specification_init(Specification* spec) {
    spec->z_safe_height = 40;
    spec->stepper_x_dir = 11;
    spec->stepper_x_stp = 12;
    spec->stepper_y_dir = 13;
    spec->stepper_y_stp = 15;
    spec->stepper_z_dir = 16;
    spec->stepper_z_stp = 18;
}