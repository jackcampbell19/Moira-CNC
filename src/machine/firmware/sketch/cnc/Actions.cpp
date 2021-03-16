#include "Actions.h"
#include <string.h>

void do_nothing(Hardware* hardware, Screen* screen) {}

void back(Hardware* hardware, Screen* screen) {
  hardware->setScreen(screen->superScreen->superScreen);
}

void display_screen(Hardware* hardware, Screen* screen) {
  hardware->setScreen(screen);
}

void set_origin(Hardware* hardware, Screen* screen) {
  hardware->x.setPosition(0);
  hardware->y.setPosition(0);
  hardware->z.setPosition(0);
  hardware->lcd.clear();
  hardware->lcd.setCursor(0, 0);
  hardware->lcd.print("Origin Set");
  delay(1000);
}

void helper_display_current_position(Hardware* hardware) {
  hardware->lcd.clear();
  hardware->lcd.setCursor(0, 0);
  char str[16];
  snprintf(str, 15, "%d/%d/%d", (int) hardware->x.getPosition(), (int) hardware->y.getPosition(), (int) hardware->z.getPosition());
  hardware->lcd.print(str);
}

void helper_move_axis(Stepper* stepper, Hardware* hardware, int steps) {
  helper_display_current_position(hardware);
  while (1) {
    int s = 0;
    RotaryEncoderState state = hardware->rotaryEncoder.getState();
    if (state == CW) {
      s = steps;
    } else if (state == CCW) {
      s = -steps;
    } else if (state == BP) {
      return;
    } else if (state == NONE) {
      delay(1);
      continue;
    }
    stepper->setTargetRel(s);
    hardware->controller.move(*stepper);
    while (hardware->controller.isRunning()) {
      delay(10);
    }
    helper_display_current_position(hardware);
    delay(1);
  }
}

void move_x_500(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->x, hardware, 500);
}

void move_x_100(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->x, hardware, 100);
}

void move_x_10(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->x, hardware, 10);
}

void move_x_1(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->x, hardware, 1);
}

void move_y_500(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->y, hardware, 500);
}

void move_y_100(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->y, hardware, 100);
}

void move_y_10(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->y, hardware, 10);
}

void move_y_1(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->y, hardware, 1);
}

void move_z_500(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->z, hardware, 500);
}

void move_z_100(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->z, hardware, 100);
}

void move_z_10(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->z, hardware, 10);
}

void move_z_1(Hardware* hardware, Screen* screen) {
  helper_move_axis(&hardware->z, hardware, 1);
}

void pick_file_from_sd(Hardware* hardware, Screen* screen) {
  hardware->lcd.clear();
  hardware->lcd.setCursor(0, 0);
  hardware->lcd.print("Insert SD...");
  while (!hardware->sd.isInserted()) {
    if (hardware->rotaryEncoder.getState() == BP) {
      return;
    }
    delay(1);
  }
  hardware->sd.initRoot();
  hardware->lcd.clear();
  hardware->lcd.setCursor(0, 0);
  hardware->lcd.print("Loading...");
  char filenames[128][16];
  int fileCount = hardware->sd.getFilenames(filenames);
  if (fileCount == 0) {
    hardware->lcd.clear();
    hardware->lcd.setCursor(0, 0);
    hardware->lcd.print("No files found");
    while (1) {
      if (hardware->rotaryEncoder.getState() == BP) {
        return;
      }
      delay(1);
    }
  }
  int i = 0;
  hardware->lcd.clear();
  hardware->lcd.setCursor(0, 0);
  char fn[16];
  snprintf(fn, 15, "%d. %s", i, filenames[i]);
  hardware->lcd.print(fn);
  while (1) {
    RotaryEncoderState state = hardware->rotaryEncoder.getState();
    if (state == CW) {
      ++i;
      if (i > fileCount - 1) {
        i = fileCount - 1;
      }
      hardware->lcd.clear();
      hardware->lcd.setCursor(0, 0);
      char fn[16];
      snprintf(fn, 15, "%d. %s", i, filenames[i]);
      hardware->lcd.print(fn);
    } else if (state == CCW) {
      --i;
      if (i < 0) {
        i = 0;
      }
      hardware->lcd.clear();
      hardware->lcd.setCursor(0, 0);
      char fn[16];
      snprintf(fn, 15, "%d. %s", i, filenames[i]);
      hardware->lcd.print(fn);
    } else if (state == BP) {
      hardware->lcd.clear();
      hardware->lcd.setCursor(0, 0);
      hardware->lcd.print("Selected:");
      hardware->lcd.setCursor(0, 1);
      hardware->lcd.print(filenames[i]);
      hardware->sd.openMi(filenames[i]);
      hardware->sd.hasFile = 1;
      delay(1000);
      return;
    }
    delay(1);
  }
}

void run_file(Hardware* hardware, Screen* screen) {
  if (!hardware->sd.hasFile) {
    hardware->lcd.clear();
    hardware->lcd.setCursor(0, 0);
    hardware->lcd.print("No file selected");
    delay(1000);
    return;
  }
  hardware->lcd.clear();
  hardware->lcd.setCursor(0, 0);
  hardware->lcd.print("Running...");
  char instruction[32];
  while (hardware->sd.getNextInstruction(instruction, 32)) {
    hardware->executeInstruction(instruction);
  }
}
