//
// Created by Callixte Muller on 12/01/2026.
//

#include "picture.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

picture new_pic(int height, int width) {
    color *pixels = malloc(sizeof(color) * width * height);
    picture pic = {width, height, pixels};

    return pic;
}

void save_pic(picture pic, char *filename) {
    FILE *fptr = fopen(filename, "w");

    image img = {"P6", pic.width, pic.height, 255};

    fprintf(fptr, "%s\n%d %d\n%d\n", img.fileSign, img.width, img.height, img.intensity);

    for (int i = 0; i < pic.height * pic.width; i++) {
        fwrite(&pic.pixels[i], sizeof(color), 1, fptr);
    }

    free(pic.pixels);
    fclose(fptr);
}

void set_pixel(picture *pic, int x, int y, color pixel) {
    if (!pic || !pic->pixels) return;
    if (x < 0 || x >= pic->width || y < 0 || y >= pic->height) return;


    if ((x == 0 || x == pic->width - 1) && (y == 0 || y == pic->height - 1)) {
        pixel.red = 255;
        pixel.green = 125;
        pixel.blue = 125;
    } else {
        pixel.red = 0;
        pixel.green = 0;
        pixel.blue = 0;
    }

    pic->pixels[y * pic->width + x] = pixel;
}

void draw_line(picture *pic, int x0, int y0, int x1, int y1, color c) {
    if (!pic || !pic->pixels) return;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int n = (dx >dy ? dx : dy) + 1;
    if (n <= 0) return;

    double step_x = (n>1) ? (double)(x1-x0) / (n-1): 0.0;
    double step_y = (n>1) ? (double)(y1-y0) / (n-1): 0.0;

    for (int i = 0; i < n; i++) {
        int x = x0 + (int)round(step_x * i);
        int y = y0 + (int)round(step_y * i);

        if (x >= 0 && x < pic->width && y >= 0 && y < pic->height) {
            pic->pixels[y * pic->width + x] = c;
        }
    }
}

void add_pic_background(picture *pic, color background_color) {
    if (!pic || !pic->pixels) return;

    for (int x = 0; x < pic->width; x++) {
        for (int y = 0; y < pic->height; y++) {
            pic->pixels[y * pic->width + x] = background_color;
        }
    }
}

void sierpinski(picture *pic, int x, int y, int size, color c) {
    if (!pic || !pic->pixels) return;

    double triangle_height = size * sqrt(3.0) / 2.0;

    double left_x = x + size - 1;
    double left_y = y;

    double right_x = x + size / 2.0;
    double right_y = y - triangle_height;

    int x0 = (int)round(x);
    int y0 = (int)round(y);
    int x1 = (int)round(left_x);
    int y1 = (int)round(left_y);
    int x2 = (int)round(right_x);
    int y2 = (int)round(right_y);

    draw_line(pic, x0, y0, x1, y1, c);
    draw_line(pic, x0, y0, x2, y2, c);
    draw_line(pic, x1, y1, x2, y2, c);

    printf("sommet %d, %d\n", x0, y0);
    printf("left %d, %d\n", x1, y1);
    printf("right %d, %d\n", x2, y2);
}

void sierpinski_div(picture *pic, int x, int y, int size, color c) {
    if (!pic || !pic->pixels) return;

    sierpinski(pic, x, y, size/2, c);
    sierpinski(pic, x + size/2, y, size/2, c);
    sierpinski(pic, x + size/2, y-size*sqrt(3)/4, size/2, c);
}