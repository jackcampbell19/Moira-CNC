#pragma once

#include "Hardware.h"

void do_nothing(Hardware* hardware, Screen* screen);
void back(Hardware* hardware, Screen* screen);
void display_screen(Hardware* hardware, Screen* screen);
void set_origin(Hardware* hardware, Screen* screen);
void helper_display_current_position(Hardware* hardware);
void helper_move_axis(Stepper* stepper, StepControl controller, int steps);
void move_x_500(Hardware* hardware, Screen* screen);
void move_x_100(Hardware* hardware, Screen* screen);
void move_x_10(Hardware* hardware, Screen* screen);
void move_x_1(Hardware* hardware, Screen* screen);
void move_y_500(Hardware* hardware, Screen* screen);
void move_y_100(Hardware* hardware, Screen* screen);
void move_y_10(Hardware* hardware, Screen* screen);
void move_y_1(Hardware* hardware, Screen* screen);
void move_z_500(Hardware* hardware, Screen* screen);
void move_z_100(Hardware* hardware, Screen* screen);
void move_z_10(Hardware* hardware, Screen* screen);
void move_z_1(Hardware* hardware, Screen* screen);
void pick_file_from_sd(Hardware* hardware, Screen* screen);
void run_file(Hardware* hardware, Screen* screen);
