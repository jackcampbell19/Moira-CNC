#pragma once

#include <SD.h>
#include <SPI.h>


/**
 * Access to the SD card.
*/
class SDCard {

	public:

	File root;
	File mi_file;

	SDCard();
	int isInserted();
	void initRoot();
	int findMi(char* filename);
	int openMi(char* filename);
	int getNextInstruction(char* instruction, int bufsize);
	size_t getFilenames(char filenames[48][128]);

};
