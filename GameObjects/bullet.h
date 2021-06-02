#ifndef BULLET_H
#define BULLET_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../GameObjects/ship.h"
#include "../Handlers/mathHandler.h"
#include "../Handlers/global.h"

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

#endif //BULLET_H


typedef struct {
    vec3d pos;
    vec3d dir;
    float size;
    float velocity;
    bool activated;

    float r, g, b;
} bullet;

void initBullet(bullet *bullet, ship *ship);

void drawBullet(bullet *bullet);

void moveBullet(bullet *bullet, float deltaTime);

void bulletCollision(bullet *bullet);
