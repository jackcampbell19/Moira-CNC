#include "Sequence.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../vector/Vector.h"

/**
 * Calculates sequence of steps to take to draw a line with a given x, y, z coordinates from s to e.
*/
void sequence_generate(Sequence* sequence, Vector* s, Vector* e) {
    // Init sequence default
    sequence->count = 0;
    // Begin calulation
    Vector d;
    vector_subtract(e, s, &d);
    double m = round(vector_norm(&d));
    if (m == 0) {
        return;
    }
    double f = 1.0 / m;
    Vector last_position;
    vector_zero(&last_position);
    double scalar = 0;
    sequence->steps = (Vector*) malloc(sizeof(Vector) * (m + 1));
    Vector vector_position;
    Vector dv;
    for (size_t i = 0; i <= (size_t) m; i++) {
        vector_multiply(&d, scalar, &vector_position);
        vector_round_t(&vector_position);
        vector_subtract(&vector_position, &last_position, &dv);
        if (vector_norm(&dv) > 0) {
            vector_floor_t(&dv);
            vector_copy(&sequence->steps[sequence->count], &dv);
            sequence->count++;
        }
        vector_copy(&last_position, &vector_position);
        scalar += f;
    }
    
}
