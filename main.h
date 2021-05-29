#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "CoreGraphics/CoreGraphics.h"
#include "Managers/cameraManager.h"
#include "GameObjects/arena.h"
#include "GameObjects/ship.h"

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

#define KEY_ESC 27

typedef struct {
    bool movingForward;
    bool movingBackward;
    bool rollingLeft;
    bool rollingRight;
    bool restartGame;
} keyHandler;

int main(int argc, char **argv);

void initGame();

void initKeyHandler();

void onReshape(int w, int h);

void onDisplay();

void onIdle();

void updateGameState(camera *camera, ship *ship, float deltaTime);

void renderFrame();

void onKeyPress(unsigned char key, int x, int y);

void onKeyUp(unsigned char key, int x, int y);

void onMousePress(int state, int button, int x, int y);

void onMouseMove(int x, int y);

#endif //MAIN_H