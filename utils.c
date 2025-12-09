#include "utils.h"
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int convergence(float x, float y) {
    float complex Z = CMPLXF(x, y);
    float complex U = Z;

    float r2 = sqrtf(crealf(U) * crealf(U) + cimagf(U) * cimagf(U));
    if (r2 >= 2.0f) return 0;

    for (int i = 1; i <= 85; i++) {
        U = U*U+Z;

        r2 = sqrtf(crealf(U) * crealf(U) + cimagf(U) * cimagf(U));
        if (r2 >= 2.0f) {
            return i;
        }
    }
    return 0;
}

color palette(int c) {

    struct Color color = {};

    int c_res = c % 1785;

    if (c_res >= 0 && c_res <= 255){
        color.red = c_res;
        color.green = 0;
        color.blue = 0;
    } else if (c_res >= 255 && c_res <= 510) {
        color.red = 255;
        color.green = c_res-255;
        color.blue = 0;
    } else if (c_res >= 510 && c_res <= 765) {
        color.red = 765-c_res;
        color.green = 255;
        color.blue = 0;
    } else if (c_res >= 765 && c_res <= 1020) {
        color.red = 0;
        color.green = 255;
        color.blue = 1020-c_res;
    } else if (c_res >= 1020 && c_res <= 1275) {
        color.red = 0;
        color.green = 1275-c_res;
        color.blue = 255;
    } else if (c_res >= 1275 && c_res <= 1530) {
        color.red = c_res - 1530;
        color.green = 0;
        color.blue = 255;
    } else if (c_res >= 1530 && c_res <= 1785) {
        color.red = 255;
        color.green = 0;
        color.blue = 1785-c_res;
    }

    return color;
}

#include <stdlib.h>

mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale) {
    int Xmax = Xmin + (scale * 3.0);
    int Ymax = Ymin + (scale * 3.0 * height / width);
    int pixWidth = scale * (3.0 / width);
    int *cnvgr = malloc(sizeof(int) * width * height);
    if (!cnvgr) {
        mandel_pic empty = {0};
        return empty;
    }

    const double xStep = (double)(X2_VALUE - X1_VALUE) / width;
    const double yStep = (double)(Y2_VALUE - Y1_VALUE) / height;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            double x = (double)X1_VALUE + i * xStep;
            double y = (double)Y1_VALUE + j * yStep;

            int c = convergence((float)x, (float)y);
            cnvgr[j * width + i] = c;
        }
    }

    mandel_pic newMandel = {width, height, Xmin, Ymin, Xmax, Ymax, scale, pixWidth, cnvgr};
    return newMandel;
}


void save_mandel(mandel_pic mandel, char* filename) {
    FILE *fptr = fopen(filename, "w");

    struct image img = {"P6", mandel.width, mandel.height, 255};

    fprintf(fptr, "%s\n%d %d\n%d\n", img.fileSign, img.width, img.height, img.intensity);

    for (int j= 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {

            int c = mandel.convrg[j*mandel.width+i];

            struct Color color = palette(c * 10);
            fwrite(&color,  1, 3, fptr);
        }
    }

    free(mandel.convrg);
    fclose(fptr);
}