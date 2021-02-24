#include "hardware/CNC.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Primary entry point for the CNC program. Generates instance of the CNC and 
 * initilizes its functionality.
*/
int main(int argc, char *argv[]) {
    CNC cnc;
    cnc_init(&cnc);
    if (argc != 2) {
        return 1;
    }
    char* path = argv[1];
    cnc_run_mi(&cnc, path);
    return 0;
}