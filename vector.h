//
// Created by Callixte Muller on 22/01/2026.
//

#ifndef MINI_PROJET_VECTOR_H
#define MINI_PROJET_VECTOR_H
#include "picture.h"

typedef struct vector {
    double x1;
    double y1;
    double x2;
    double y2;

    struct vector *next;
}vec;

vec *read_vector_file(char *filename);

void draw_vector(vec *vector, picture *pic, color c);

void scale_vector(vec *vector, double scale);

void shift_vector(vec *vector, double x, double y);

void flip_vector(vec *vector);

#endif //MINI_PROJET_VECTOR_H