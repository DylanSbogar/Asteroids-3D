#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Managers/cameraManager.h"
#include "Managers/inputManager.h"

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

int main(int argc, char **argv);

void initGame();

void onReshape(int w, int h);

void onDisplay();

void onIdle();

void updateGameState();

#endif //MAIN_H