#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Handlers/mathHandler.h"
#include "../Handlers/global.h"
#include "arena.h"
#include "ship.h"

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
    vec3d vertices[ASTEROID_DIVISIONS + 1][ASTEROID_DIVISIONS + 1];
    vec3d pos;
    vec3d dir;
    int size;
    float velocity;
    float r, g, b; // DEBUG colour of asteroid.
    // float rotateVelocity;
    bool activated; // Is set to true when the asteroid enters the arena.
    bool alive;
} asteroid;

void initAsteroid(asteroid *asteroid, ship *ship);

void drawAsteroid(asteroid *asteroid);

void moveAsteroid(asteroid *asteroid, float deltaTime, int round);

bool asteroidWallCollision(asteroid *asteroid);

void checkActivated(asteroid *asteroid);

bool asteroidShipCollision(ship *ship, asteroid *asteroid);

#endif //ASTEROID_H