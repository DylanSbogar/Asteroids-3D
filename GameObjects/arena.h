#ifndef ARENA_H
#define ARENA_H

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

#define WALL_SEGMENTS 10
#define ARENA_RADIUS 10

typedef struct {
    int x;
    int y;
    int z;
} wall;

void drawAxes();

wall initWall(int x, int y, int z);

void drawWall(wall *wall);

void drawArena();

#endif //ARENA_H