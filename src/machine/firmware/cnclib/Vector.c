#include "Vector.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


// Prints a vector
void vector_print(Vector* v) {
    printf("Vector(%f, %f, %f)\n", v->x, v->y, v->z);
}


// Constructs a vector with the given args
void vector_construct(Vector* v, double x, double y, double z) {
    v->x = x;
    v->y = y;
    v->z = z;
}


// Creates a vector and returns the pointer
Vector* vector_alloc_create(double x, double y, double z) {
    Vector* v = (Vector*) malloc(sizeof(Vector));
    vector_construct(v, x, y, z);
    return v;
}


// Returns pointer to a zero vector
void vector_zero(Vector* v) {
    vector_construct(v, 0, 0, 0);
}


// Copies a v1 to v0
void vector_copy(Vector* v0, Vector* v1) {
    v0->x = v1->x;
    v0->y = v1->y;
    v0->z = v1->z;
}


// Adds v1 to v0 and storees the result in r
void vector_add(Vector* v0, Vector* v1, Vector* r) {
    r->x = v0->x + v1->x;
    r->y = v0->y + v1->y;
    r->z = v0->z + v1->z;
}


// Adds v1 vector to v0 vector
void vector_add_t(Vector* v0, Vector* v1) {
    vector_add(v0, v1, v0);
}


// Subtracts v1 from v0
void vector_subtract(Vector* v0, Vector* v1, Vector* r) {
    r->x = v0->x - v1->x;
    r->y = v0->y - v1->y;
    r->z = v0->z - v1->z;
}


void vector_subtract_t(Vector* v0, Vector* v1) {
    vector_subtract(v0, v1, v0);
}


// Multiplies a vector by a scalar
void vector_multiply(Vector* v0, double s, Vector* r) {
    r->x = v0->x * s;
    r->y = v0->y * s;
    r->z = v0->z * s;
}


// Multiplies a vector by a scalar and returns a new pointer
void vector_multiply_t(Vector* v0, double s) {
    vector_multiply(v0, s, v0);
}


// Assigns the cross product of 2 3x3 vectors to r
void vector_cross(Vector* a, Vector* b, Vector* r) {
    r->x = a->y * b->z - a->z * b->y;
    r->y = a->z * b->x - a->x * b->z;
    r->z = a->x * b->y - a->y * b->x;
}


double vector_dot(Vector* a, Vector* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}


double vector_norm(Vector* v) {
    return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}


void vector_rotate_x(Vector* v, double angle, Vector* r) {
    double a = angle * M_PI / 180;
    double x = v->x;
    double y = v->y;
    double z = v->z;
    r->x = x;
    r->y = (y * cos(a)) - (z * sin(a));
    r->z = (y * sin(a)) + (z * cos(a));
}


void vector_rotate_y(Vector* v, double angle, Vector* r) {
    double a = angle * M_PI / 180;
    double x = v->x;
    double y = v->y;
    double z = v->z;
    r->x = x * cos(a) + z * sin(a);
    r->y = y;
    r->z = -x * sin(a) + z * cos(a);
}


void vector_rotate_z(Vector* v, double angle, Vector* r) {
    double a = angle * M_PI / 180;
    double x = v->x;
    double y = v->y;
    double z = v->z;
    r->x = x * cos(a) - y * sin(a);
    r->y = x * sin(a) + y * cos(a);
    r->z = z;
}

void vector_rotate_x_t(Vector* v, double angle) {
    vector_rotate_x(v, angle, v);
}

void vector_rotate_y_t(Vector* v, double angle) {
    vector_rotate_y(v, angle, v);
}

void vector_rotate_z_t(Vector* v, double angle) {
    vector_rotate_z(v, angle, v);
}

int vector_equals(Vector* a, Vector* b) {
    return a->x == b->x && a->y == b->y && a->z == b->z;
}

void vector_round(Vector* v0, Vector* v1) {
    v0->x = round(v1->x);
    v0->y = round(v1->y);
    v0->z = round(v1->z);
}

void vector_round_t(Vector* v) {
    vector_round(v, v);
}

void vector_floor(Vector* v0, Vector* v1) {
    v0->x = floor(v1->x);
    v0->y = floor(v1->y);
    v0->z = floor(v1->z);
}

void vector_floor_t(Vector* v) {
    vector_floor(v, v);
}