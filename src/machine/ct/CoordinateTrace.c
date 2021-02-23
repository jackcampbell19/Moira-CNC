#include "CoordinateTrace.h"
#include <string.h>

void ct_init(CoordinateTrace* ct, char* path) {
    ct->path = path;
    ct->fp = fopen(path, "r");
    if (ct->fp == NULL)
        exit(EXIT_FAILURE);
    ct->len = 128;
    ct->line = (char *) malloc(sizeof(char) * ct->len + 1);
}

int ct_nextline(CoordinateTrace* ct) {
    return fgets(ct->line, ct->len, ct->fp) != NULL;
}

void ct_close(CoordinateTrace* ct) {
    fclose(ct->fp);
    free(ct->line);
}

void ct_parse_coord(CoordinateTrace* ct, int* x, int* y, int* z) {
    char *p;
    p = strtok(&ct->line[2], ",");
    *x = atoi(p);
    p = strtok(NULL, ",");
    *y = atoi(p);
    p = strtok(NULL, ",");
    *z = atoi(p);
}
