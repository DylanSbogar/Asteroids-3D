#ifndef MATH_HANDLER_H
#define MATH_HANDLER_H

#include <math.h>
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

typedef struct {
  GLuint vb;
  int numTriangles;
} DrawObject;

#define RAD_TO_DEG(rad) (rad * (180 / M_PI))

#define DEG_TO_RAD(deg) (deg * (M_PI / 180))

#define PYTHAGORAS(x, y, z) (sqrt(pow(x,2) + pow(y,2) + pow(z,2)))

static inline vec3d distanceBetweenPoints(vec3d source, vec3d target) {
    vec3d result;

    result.x = target.x - source.x;
    result.y = target.y - source.y;
    result.z = target.z - source.z;

    return result;
}

static inline vec3d vec3dAddition(vec3d vec, vec3d vec2) {
    vec3d result;

    result.x = vec.x + vec2.x;
    result.y = vec.y + vec2.y;
    result.z = vec.z + vec2.z;

    return result;
}

static inline vec3d normalise(vec3d vec) {
    float vecLength = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    vec3d result;
    result.x = vec.x / vecLength;
    result.y = vec.y / vecLength;
    result.z = vec.z / vecLength;
    
    return result;
}

#endif //MATH_HANDLER_H
