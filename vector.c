//
// Created by Callixte Muller on 22/01/2026.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#include "picture.h"

vec *read_vector_file(char *filename) {
    vec *firstElement = NULL;
    FILE *file = fopen(filename, "r");

    float x1, y1, x2, y2;

    while (fscanf(file, "%f %f %f %f", &x1, &y1, &x2, &y2) != EOF) {
        vec *v = malloc(sizeof(vec));

        v->x1 = x1;
        v->y1 = y1;
        v->x2 = x2;
        v->y2 = y2;
        v->next = firstElement;
        firstElement = v;
    }

    fclose(file);
    return firstElement;
}

void draw_vector(vec *vector, picture *pic, color c) {
    while (vector != NULL) {
        draw_line(pic, vector->x1, vector->y1, vector->x2, vector->y2, c);
        vector = vector->next;
    }
}

void scale_vector(vec *vector, double scale) {
    while (vector != NULL) {
        vector->x1 = vector->x1 * scale;
        vector->y1 = vector->y1 * scale;
        vector->x2 = vector->x2 * scale;
        vector->y2 = vector->y2 * scale;
        vector = vector->next;
    }
}

void shift_vector(vec *vector, double x, double y) {
    while (vector != NULL) {
        vector->x1 += x;
        vector->y1 += y;
        vector->x2 += x;
        vector->y2 += y;
        vector = vector->next;
    }
}

void flip_vector(vec *vector) {
    while (vector != NULL) {
        vector->x1 = -vector->x1;
        vector->x2 = -vector->x2;
        vector = vector->next;
    }
}