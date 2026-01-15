#include <stdio.h>
#include "main.h"
#include "picture.h"

int main() {
    // squareImage();
    // roundImage();

    picture pic = new_pic(350, 400);
    picture square = new_pic(10, 10);
    color red = {255, 0, 0};
    color blue = {0, 0, 255};
    color green = {0, 255, 0};
    color magenta = {255, 0, 255};
    color white = {255, 255, 255};
    color yellow = {255, 255, 0};
    // for (int i = 0; i < pic.height; i++) {
    //     for (int j = 0; j < pic.width; j++) {
    //         set_pixel(&pic, i, j, c);
    //     }
    // }
    add_pic_background(&pic, white);
    draw_line(&square, 2, 2, 7, 7, red);
    draw_line(&square, 2, 5, 7, 2, blue);
    draw_line(&square, 1, 2, 1, 7, green);
    draw_line(&square, 8, 2, 8, 7, green);
    draw_line(&square, 2, 1, 7, 1, magenta);
    draw_line(&square, 2, 8, 7, 8, magenta);

    // sierpinski(&pic, 0, 349, 400, magenta);
    sierpinski_div(&pic, 0, 349, 400, magenta);

    save_pic(pic, "pic.ppm");
    save_pic(square, "square.ppm");

    return 0;
}

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