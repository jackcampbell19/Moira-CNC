#include "MachineLog.h"
#include <Arduino.h>


/**
 * Writes out a line to the log.
*/
void MachineLog::write(const char* line) {
	Serial.println(line);
}