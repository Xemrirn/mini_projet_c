#include "utils.h"
#include <complex.h>
#include <math.h>
#include <stdio.h>

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

mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale) {
    int Xmax = Xmin + (scale * 3.0);
    int Ymax = Ymin + (scale * 3.0 * height / width);
    int pixWidth = scale * (3.0 / width);
    int * cnvgr = 0;

    const double xStep = (double)(X2_VALUE - X1_VALUE) / width;
    const double yStep = (double)(Y2_VALUE - Y1_VALUE) / height;

    for (int j= 0; j < 600; j++) {
        for (int i = 0; i < 900; i++) {
            double x = (double)X1_VALUE + i * xStep;
            double y = (double)Y1_VALUE + j * yStep;

            double c = convergence(x, y);

            cnvgr[i+j] = c;
        }
    }

    mandel_pic newMandel = {width, height, Xmin, Ymin, Xmax, Ymax, scale, pixWidth, cnvgr};

    return newMandel;
}