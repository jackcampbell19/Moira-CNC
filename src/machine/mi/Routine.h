#if !defined(ROUTINE)
#define ROUTINE

#include <stdlib.h>

struct Routine_ {
	int instruction_count;
	char** instructions;
};
typedef struct Routine_ Routine;

void routine_init(Routine* routine, int instruction_count);
void routine_free(Routine* routine);

#endif // ROUTINE
