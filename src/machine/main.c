#include "hardware/CNC.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Primary entry point for the CNC program. Generates instance of the CNC and 
 * initilizes its functionality.
*/
int main(int argc, char *argv[]) {
    CNC* cnc = (CNC*) malloc(sizeof(CNC));
    cnc_init(cnc);
    if (argc != 2) {
        return 1;
    }
    // TODO: create ct file
    
    return 0;
}