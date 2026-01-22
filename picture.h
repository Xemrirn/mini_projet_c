//
// Created by Callixte Muller on 12/01/2026.
//

#ifndef MINI_PROJET_PICTURE_H
#define MINI_PROJET_PICTURE_H
#include "utils.h"

picture new_pic(int height, int width);

void save_pic(picture pic, char *filename);

void set_pixel(picture *pic, int x, int y, color pixel);

void draw_line(picture *pic, int x0, int y0, int x1, int y1, color c);

void add_pic_background(picture *pic, color background_color);

void sierpinski(picture *pic, int x, int y, int size, color c);

void sierpinski_div(picture *pic, int x, int y, int size, color c);

void drawCat();

vec *read_vector_file(char *filename);

void draw_vector(vec *vector, picture *pic, color c);

void scale_vector(vec *vector, double scale);

void shift_vector(vec *vector, double x, double y);

void flip_vector(vec *vector);

#endif //MINI_PROJET_PICTURE_H