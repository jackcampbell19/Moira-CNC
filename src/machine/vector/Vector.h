#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct {
    double x;
    double y;
    double z;
} Vector;

void vector_print(Vector* v);
void vector_construct(Vector* v, double x, double y, double z);
Vector* vector_alloc_create(double x, double y, double z);
void vector_zero(Vector* v);
void vector_copy(Vector* v0, Vector* v1);

void vector_add(Vector* v0, Vector* v1, Vector* r);
void vector_add_t(Vector* v0, Vector* v1);

void vector_subtract(Vector* v0, Vector* v1, Vector* r);
void vector_subtract_t(Vector* v0, Vector* v1);

void vector_multiply(Vector* v0, double s, Vector* r);
void vector_multiply_t(Vector* v0, double s);

void vector_cross(Vector* a, Vector* b, Vector* r);
double vector_dot(Vector* a, Vector* b);
double vector_norm(Vector* v);

void vector_rotate_x(Vector* v, double angle, Vector* r);
void vector_rotate_y(Vector* v, double angle, Vector* r);
void vector_rotate_z(Vector* v, double angle, Vector* r);
void vector_rotate_x_t(Vector* v, double angle);
void vector_rotate_y_t(Vector* v, double angle);
void vector_rotate_z_t(Vector* v, double angle);

int vector_equals(Vector* a, Vector* b);
void vector_round(Vector* v0, Vector* v1);
void vector_round_t(Vector* v);

void vector_floor(Vector* v0, Vector* v1);
void vector_floor_t(Vector* v);

#endif
