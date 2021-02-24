#include "Routine.h"
#include <stdlib.h>

void routine_init(Routine* routine, int instruction_count) {
	routine->instruction_count = instruction_count;
	routine->instructions = (char**) malloc(sizeof(char*) * instruction_count);
}

void routine_free(Routine* routine) {
	for (size_t i = 0; i < routine->instruction_count; i++) {
		free(routine->instructions[i]);
	}
	free(routine->instructions);
}