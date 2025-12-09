#include "fractale.h"
#include "utils.h"
#include <stdio.h>

void drawImage() {
    FILE *fptr = fopen("fractale.ppm", "w");

    struct image img = {"P6", 900, 600, 255};

    const double xStep = (double)(X2_VALUE - X1_VALUE) / img.width;
    const double yStep = (double)(Y2_VALUE - Y1_VALUE) / img.height;

    fprintf(fptr, "%s\n%d %d\n%d\n", img.fileSign, img.width, img.height, img.intensity);

    for (int j= 0; j < 600; j++) {
        for (int i = 0; i < 900; i++) {
            double x = (double)X1_VALUE + i * xStep;
            double y = (double)Y1_VALUE + j * yStep;

            double c = convergence(x, y);

            // struct Pixel pixel = {120, c*3, 255};

            struct Color color = palette(c * 5);

            fwrite(&color,  1, 3, fptr);
        }
    }

    fclose(fptr);
}