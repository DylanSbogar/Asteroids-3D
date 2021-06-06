#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

#include "../Handlers/mathHandler.h"
#include "../Handlers/global.h"

typedef struct {
    vec3d pos;
    vec3d dir;
    float radius;
    float velocity;
} particle;

void particleController(float deltaTime);

void initParticle(particle *particle, vec3d pos, vec3d dir);

void launchParticle(particle *particle, vec3d pos, vec3d dir);

void moveParticle(particle *particle, float deltaTime);

void drawParticle(particle *particle);

#endif //PARTICLE_H
