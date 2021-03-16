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
  int hasFile = 0;

	SDCard();
	int isInserted();
	void initRoot();
	int findMi(char* filename);
	int openMi(char* filename);
	int getNextInstruction(char* instruction, int bufsize);
	int getFilenames(char filenames[128][16]);

};
