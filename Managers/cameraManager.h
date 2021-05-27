#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Handlers/mathHandler.h"
#include "../GameObjects/ship.h"

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

#define MOVE_VELOCITY 2.5

typedef struct {
    vec3d pos;
    vec3d look;
    vec3d up;
    float pitch, yaw, roll;
    int lastX, lastY;
    bool warpedCursor;
} camera;

void initCamera(camera *camera);

void placeCamera(camera *camera);

void updateCameraPosition(camera *camera, ship *ship);

#endif //CAMERA_MANAGER_H
