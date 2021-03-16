#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
#include "SDCard.h"

/**
 * Inits the SD card object.
*/
SDCard::SDCard() {
	// TODO
}

/**
 * Returns true if there is an SD card inserted.
*/
int SDCard::isInserted() {
	return SD.begin(BUILTIN_SDCARD);
}


void SDCard::initRoot() {
	this->root = SD.open("/");
}


int SDCard::getFilenames(char filenames[128][16]) {
	  int count = 0;
  	while(true) {
		File entry =  this->root.openNextFile();
    	if (!entry)
      		break;
    	if (entry.isDirectory())
      		continue;
    	char* name = entry.name();
    	strncpy(filenames[count], name, 16);
    	entry.close();
    	++count;
  	}
  	return count;
}


int SDCard::openMi(char* filename) {
	this->mi_file = SD.open(filename);
	if (this->mi_file) {
		return 1;
	}
	return 0;
}


int SDCard::getNextInstruction(char* instruction, int bufsize) {
	// Reset the instruction
	memset(instruction, '\0', bufsize);
	// Read chars into the instruction until the newline char
	int index = 0;
	while (this->mi_file.available()) {
        // Get the instruction
        const char character = this->mi_file.read();
        // Place into the buffer
        instruction[index] = character;
        // Increment index
        index++;
        // If character is end of line, reset the index and execute instruction
        if (character == '\n') {
			return 1;
        }
	}
	return 0;
}
