//
// Created by Callixte Muller on 12/01/2026.
//

#ifndef MINI_PROJET_UTILS_H
#define MINI_PROJET_UTILS_H

typedef struct Color {
    unsigned char red, green, blue;
} color;

typedef struct Picture {
    int width, height;
    color *pixels;
} picture;

typedef struct Image {
    char fileSign[4];
    int width;
    int height;
    int intensity;
}image;

#endif //MINI_PROJET_UTILS_H