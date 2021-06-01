#ifndef BULLET_H
#define BULLET_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    float velocity;
    bool activated;
} bullet;

void initBullet(bullet *bullet);

void drawBullet(bullet *bullet);

void moveBullet(bullet *bullet, float deltaTime, vec3d dir);

void bulletCollision(bullet *bullet);
