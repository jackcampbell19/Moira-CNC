#if !defined(CNC_DEF)

#include "Stepper.h"
#include "../vector/Vector.h"
#include <stdlib.h>
#include "../specification/Specification.h"

#define CNC_DEF


typedef struct {
    Stepper X;
    Stepper Y;
    Stepper Z;
    Vector current_position;
    Specification specs;
} CNC;


void cnc_init(CNC* cnc);
void cnc_set_position(CNC* cnc, Vector* new_position);


#endif // CNC_DEF
