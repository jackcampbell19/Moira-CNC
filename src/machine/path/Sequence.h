#if !defined(SEQUENCE_DEF)

#include "../vector/Vector.h"

#define SEQUENCE_DEF


typedef struct {
    int count;
    Vector* steps;
} Sequence;


void sequence_generate(Sequence* sequence, Vector* s, Vector* e);


#endif // SEQUENCE_DEF
