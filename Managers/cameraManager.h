#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

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

typedef struct {
    vec3d pos;
    vec3d look;
    vec3d up;
    float pitch, yaw, roll;
    int lastX, lastY;
    bool warpedCursor;
} camera;

void initCamera(camera *cam);

void placeCamera(camera *cam);

void updateCameraPosition();

#endif //CAMERA_MANAGER_H
