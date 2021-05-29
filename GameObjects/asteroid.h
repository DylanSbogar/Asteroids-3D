#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Handlers/mathHandler.h"
#include "ship.h"

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
#define ASTEROID_MIN_SIZE 1
#define ASTEROID_MAX_SIZE 20
#define ASTEROID_MIN_VELOCITY 25
#define ASTEROID_MAX_VELOCITY 75

typedef struct {
    vec3d vertices[ASTEROID_DIVISIONS + 1][ASTEROID_DIVISIONS + 1];
    vec3d pos;
    vec3d dir;
    int size;
    float velocity;
    float rotateVelocity;
} asteroid;

void initAsteroid(asteroid *asteroid, ship *ship);

void drawAsteroid(asteroid *asteroid);

void moveAsteroid(asteroid *asteroid, float deltaTime, int round);

#endif //ASTEROID_H