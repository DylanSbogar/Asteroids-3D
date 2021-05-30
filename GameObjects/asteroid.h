#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Handlers/mathHandler.h"
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

#define MAX_ASTEROIDS 10
#define ASTEROID_DIVISIONS 50
#define ASTEROID_MIN_SIZE 5
#define ASTEROID_MAX_SIZE 20
#define ASTEROID_MIN_VELOCITY 25
#define ASTEROID_MAX_VELOCITY 75
#define ASTEROID_SPAWN_RADIUS 1.25

typedef struct {
    vec3d vertices[ASTEROID_DIVISIONS + 1][ASTEROID_DIVISIONS + 1];
    vec3d pos;
    vec3d dir;
    int size;
    float velocity;
    float r, g, b; // DEBUG colour of asteroid.
    // float rotateVelocity;
    bool activated; // Is set to true when the asteroid enters the arena.
} asteroid;

void initAsteroid(asteroid *asteroid, ship *ship);

void drawAsteroid(asteroid *asteroid);

void moveAsteroid(asteroid *asteroid, float deltaTime, int round);

bool asteroidWallCollision(asteroid *asteroid);

void checkActivated(asteroid *asteroid);

#endif //ASTEROID_H