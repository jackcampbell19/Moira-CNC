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
	int is_inserted();
	void init_root();
	int find_mi(char* filename);
	int open_mi(char* filename);
	int get_next_instruction(char* instruction, int bufsize);

};