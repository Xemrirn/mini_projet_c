#ifndef MINI_PROJET_UTILS_H
#define MINI_PROJET_UTILS_H

#define X1_VALUE (-2)
#define Y1_VALUE 1
#define X2_VALUE 1
#define Y2_VALUE (-1)

int convergence(float x, float y);

struct Color palette(int c);

struct mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale);

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

typedef struct Color {
    unsigned char red, green, blue;
} color;

typedef struct mandel_pic {
    int width, height;
    double Xmin, Ymin;
    double Xmax, Ymax;
    double scale;
    double pixWidth;
    int * convrg;
} mandel_pic;


#endif //MINI_PROJET_UTILS_H