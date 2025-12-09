#include "utils.h"
#include <complex.h>
#include <math.h>

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