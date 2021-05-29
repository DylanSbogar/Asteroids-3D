#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Handlers/mathHandler.h"

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

#define ASTEROID_DIVISIONS 50

typedef struct {
    vec3d vertices[ASTEROID_DIVISIONS + 1][ASTEROID_DIVISIONS + 1];
    int size;
    float velocity;
    float rotateVelocity;
} asteroid;

void initAsteroid(asteroid *asteroid);

void drawAsteroid(asteroid *asteroid);

#endif //ASTEROID_H