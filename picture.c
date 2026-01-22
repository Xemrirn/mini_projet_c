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

    if (size < 75) {
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

        return;
    }

    int half = size / 2;
    int red = rand() % 255;
    int blue = rand() % 255;
    int green = rand() % 255;
    c.red = red;
    c.green = green;
    c.blue = blue;
    sierpinski(pic, x, y, half, c);
    sierpinski(pic, x + half, y, half, c);
    sierpinski(pic, x + size/4, (int)round(y - size * sqrt(3.0) / 4.0), half, c);
}


void drawCat() {
    FILE *file = fopen("cat.txt", "r");
    float x1,y1,x2,y2;

    picture cat = new_pic(500, 500);
    color c = {255, 127, 100};
    while (fscanf(file, "%f %f %f %f", &x1, &y1, &x2, &y2) != EOF) {
        draw_line(&cat, x1, y1, x2, y2, c);
    }

    fclose(file);
    save_pic(cat, "cat.png");
}