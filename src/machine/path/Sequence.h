#if !defined(SEQUENCE_DEF)
#define SEQUENCE_DEF

typedef struct Vector_ Vector;

struct Sequence_ {
    int count;
    Vector* steps;
};
typedef struct Sequence_ Sequence;

void sequence_generate(Sequence* sequence, Vector* s, Vector* e);

#endif // SEQUENCE_DEF
