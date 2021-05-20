#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

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
    bool turningLeft;
    bool turningRight;
    bool restartGame;
} keyHandler;

void onKeyPress(unsigned char key, int x, int y);

void onKeyUp(unsigned char key, int x, int y);

void onMousePress(int state, int button, int x, int y);

void onMouseMove(int x, int y);

#endif //INPUT_MANAGER_H
