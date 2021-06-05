#ifndef MAIN_H
#define MAIN_H

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "Handlers/tinyobj_loader_c.h"
#include <float.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "CoreGraphics/CoreGraphics.h"
#include "Managers/cameraManager.h"
#include "GameObjects/asteroid.h"
#include "GameObjects/bullet.h"
#include "GameObjects/arena.h"
#include "GameObjects/ship.h"
#include "Handlers/global.h"

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
    bool zoomingIn;
    bool zoomingOut;
} keyHandler;

int main(int argc, char **argv);

void initGame();

void initKeyHandler();

void onReshape(int w, int h);

void onDisplay();

void onIdle();

void updateGameState(camera *camera, ship *ship, float deltaTime);

void renderFrame();

void restartGame();

void onKeyPress(unsigned char key, int x, int y);

void onKeyUp(unsigned char key, int x, int y);

void onMousePress(int state, int button, int x, int y);

void onMouseMove(int x, int y);

void initLighting();

// MODEL LOADING BELOW HERE

static void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3]);

static char* mmap_file(size_t* len, const char* filename);

static char* get_dirname(char* path);

static void get_file_data(void* ctx, const char* filename, const int is_mtl, const char* obj_filename, char** data, size_t* len);

static int LoadObjAndConvert(float bmin[3], float bmax[3], const char* filename);

#endif //MAIN_H