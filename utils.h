#ifndef MINI_PROJET_UTILS_H
#define MINI_PROJET_UTILS_H

#define X1_VALUE (-2)
#define Y1_VALUE 1
#define X2_VALUE 1
#define Y2_VALUE (-1)

int convergence(float x, float y);

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

#endif //MINI_PROJET_UTILS_H