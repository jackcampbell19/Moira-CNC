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

size_t SDCard::getFilenames(char filenames[16][128]) {
	size_t count = 0;
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


/**
 * Traverses over the root and gets the filename of the '.mi' file and copies it
 * to the filename parameter. Returns true if a file is found.
*/
int SDCard::findMi(char* filename) {
	// Iterate over files
  	while(true) {
		File entry =  this->root.openNextFile();
    	// Break if there are no more files
    	if (!entry) {
      		break;
    	}
    	// Continue if the entry is a directory
    	if (entry.isDirectory()) {
      		continue;
    	}
    	// Get entry info
    	char* name = entry.name();
    	// Check file extension
		// TODO: FIX THIS
    	char target[] = "example.mi";
    	if (!strcmp(name, target)) {
    		continue;
    	}
    	// Copy filename
    	strcpy(filename, name);
    	// Close the entry
    	entry.close();
    	// Return true
    	return 1;
  	}
	// Return false
  	return 0;
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
