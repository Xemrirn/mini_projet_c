#include "fractale.h"
#include <complex.h>
#include <stdio.h>
#include <math.h>
#include "main.h"

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

void drawImage() {
    FILE *fptr = fopen("fractale.ppm", "w");

    struct image img = {"P6", 900, 600, 255};

    const double xStep = (double)(X2_VALUE - X1_VALUE) / img.width;
    const double yStep = (double)(Y2_VALUE - Y1_VALUE) / img.height;

    fprintf(fptr, "%s\n%d %d\n%d\n", img.fileSign, img.width, img.height, img.intensity);

    for (int j= 0; j < 900; j++) {
        for (int i = 0; i < 600; i++) {
            double x = (double)X1_VALUE + i * xStep;
            double y = (double)Y1_VALUE + j * yStep;

            double c = convergence(x, y);

            struct Pixel pixel = {120, c*3, 255};

            fwrite(&pixel,  1, 3, fptr);
        }
    }

    fclose(fptr);
}

int main() {
    drawImage();

    return 0;
}