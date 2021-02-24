#if !defined(MI)
#define MI

#include <stdio.h>
#include <stdlib.h>

typedef struct Routine_ Routine;
typedef struct Vector_ Vector;
typedef struct CNC_ CNC;

struct MachineInstruction_ {
    char* path;
    FILE* fp;
    size_t len;
    char* line;
    Routine** routines;
    int defined_routine_count;
};
typedef struct MachineInstruction_ MachineInstruction;

void mi_init(MachineInstruction* mi, char* path);
int mi_nextline(MachineInstruction* mi);
void mi_close(MachineInstruction* mi);

void mi_parse_coord(MachineInstruction* mi, CNC* cnc, char* instruction, Vector* coordinate);
void mi_parse_defined_routine_count(MachineInstruction* mi, char* instruction);
void mi_parse_define_routine(MachineInstruction* mi, char* instruction, int* id, int* count);
void mi_store_routine_instruction(MachineInstruction* mi, char* instruction, int id, int index);
void mi_parse_routine_instruction(MachineInstruction* mi, char* instruction, int* id);
void mi_parse_wait_instruction(MachineInstruction* mi, char* instruction, int* milliseconds);

#endif // MI
