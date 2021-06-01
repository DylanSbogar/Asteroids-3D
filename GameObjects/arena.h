#ifndef ARENA_H
#define ARENA_H

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

#define WALL_SEGMENTS 20
#define ARENA_RADIUS 250

typedef struct {
    vec3d pos;
    float r, g, b;
} wall;

void drawAxes();

void drawWall(wall *wall, float *colour);

void drawArena();

void shipWarning(ship *ship);

bool shipCollision(ship *ship);

#endif //ARENA_H