#ifndef ARENA_H
#define ARENA_H

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

#define WALL_SEGMENTS 20
#define ARENA_RADIUS 250

typedef struct {
    vec3d pos;
    float colour[];
} wall;

void drawAxes();

void initWall(wall *wall);

void drawWall(wall *wall);

void drawArena();

#endif //ARENA_H