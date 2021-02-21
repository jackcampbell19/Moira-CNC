#if !defined(CT)
#define CT

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* path;
    FILE* fp;
    size_t len;
    char* line;
} CoordinateTrace;

void ct_init(CoordinateTrace* ct, char* path);
int ct_nextline(CoordinateTrace* ct);
void ct_close(CoordinateTrace* ct);
void ct_parse_coord(CoordinateTrace* ct, int* x, int* y, int* z);

#endif // CT
