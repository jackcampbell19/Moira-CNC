#if !defined(CNC_DEF)
#define CNC_DEF

#include <stdlib.h>
#include "Stepper.h"
#include "Vector.h"

struct CNC_ {
    Stepper X;
    Stepper Y;
    Stepper Z;
    Vector current_position;
};
typedef struct CNC_ CNC;


void cnc_init(CNC* cnc, int x_dir, int x_stp, int y_dir, int y_stp, int z_dir, int z_stp);
void cnc_set_position(CNC* cnc, Vector* new_position);
void cnc_execute_instruction(CNC* cnc, char* instruction);
Vector* sequence_generate(Vector* s, Vector* e, int* count);


#endif // CNC_DEF
