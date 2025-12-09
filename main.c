#include <stdio.h>
#include "main.h"
#include "fractale.h"
#include "utils.h"

void squareImage() {
    FILE *fptr = fopen("img.ppm", "w");

    const struct Pixel pixels = {122, 56, 200};
    struct image img = {"P6", 10, 10, 255};

    fprintf(fptr, "%s\n%d %d\n%d\n", img.fileSign, img.width, img.height, img.intensity);

    for (int i = 0; i < 100; i++) {
        fwrite(&pixels, 1, 3, fptr);
    }
    fclose(fptr);
}

void roundImage() {
    FILE *fptr = fopen("imgCircle.ppm", "w");

    const struct Pixel pixelAround = {122, 56, 200};
    const struct Pixel pixelCircle = {255, 56, 200};
    struct image img = {"P6", 600, 400, 255};
    fprintf(fptr, "%s\n%d %d\n%d\n", img.fileSign, img.width, img.height, img.intensity);


    const int middleX = img.width / 2;
    const int middleY = img.height / 2;
    const int radius = 200;
    const int r2 = radius * radius;

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            const int dx = x - middleX;
            const int dy = y - middleY;
            if (dx*dx + dy*dy <= r2) {
                fwrite(&pixelCircle, 1, 3, fptr);
            } else {
                fwrite(&pixelAround, 1, 3, fptr);
            }
        }
    }

    fclose(fptr);
}

int main() {
    squareImage();
    roundImage();
    drawImage();
    return 0;
}