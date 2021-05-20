#ifndef MATH_HANDLER_H
#define MATH_HANDLER_H

#include "mathHandler.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#if _WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#endif

typedef struct {
    float x;
    float y;
    float z;
} vec3d;

#define RAD_TO_DEG(rad) (rad * (180 / M_PI))

#define DEG_TO_RAD(deg) (deg * (M_PI / 180))

#define PYTHAGORAS(x, y, z) (sqrt(pow(x,2) + pow(y,2) + pow(z,2)))

static inline vec3d directionBetweenPoints(vec3d source, vec3d target) {
    vec3d result;

    result.x = target.x - source.x;
    result.y = target.y - source.y;
    result.z = target.z - source.z;

    return result;
}

#endif //MATH_HANDLER_H
