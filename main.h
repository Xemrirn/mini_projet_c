#ifndef MINI_PROJET_MAIN_H
#define MINI_PROJET_MAIN_H

struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct image {
    char fileSign[4];
    int width;
    int height;
    int intensity;
};

void squareImage();
void roundImage();

int main();

#endif