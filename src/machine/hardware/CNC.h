#if !defined(CNC_DEF)
#define CNC_DEF

#include <stdlib.h>
#include "../specification/Specification.h"
#include "Stepper.h"
#include "../vector/Vector.h"

typedef struct MachineInstruction_ MachineInstruction;

struct CNC_ {
    Stepper X;
    Stepper Y;
    Stepper Z;
    Vector current_position;
    Specification specs;
};
typedef struct CNC_ CNC;


void cnc_init(CNC* cnc);
void cnc_set_position(CNC* cnc, Vector* new_position);
void cnc_run_mi(CNC* cnc, char* path);
void cnc_execute_instruction(CNC* cnc, MachineInstruction* mi, char* instruction);


#endif // CNC_DEF
