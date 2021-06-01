#ifndef SHIP_H
#define SHIP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Handlers/mathHandler.h"
#include "../Managers/cameraManager.h"

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

#define SHIP_WARNING 2.0
#define SHIP_COLLISION 1.25

typedef struct {
    vec3d pos;
    vec3d dir;
    float velocity;
} ship;

void initShip(ship *ship, camera *camera);

void drawShip(ship *ship, float yaw, float roll, float pitch);

void moveShip(ship *ship, float deltaTime, int turnValue);

#endif //SHIP_H
