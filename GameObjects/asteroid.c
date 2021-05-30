#include "asteroid.h"

void initAsteroid(asteroid *asteroid, ship *ship) {
    // Set the position of the asteroid.
    // asteroid->pos.x = 100;
    // asteroid->pos.y = 100;
    // asteroid->pos.z = 100;
    float temp = (rand() % 360) / (double)360 * 2.0 * M_PI;
    asteroid->pos.x = (ASTEROID_SPAWN_RADIUS * cosf(temp)) * ARENA_RADIUS;
    asteroid->pos.y = (ASTEROID_SPAWN_RADIUS * sinf(temp)) * ARENA_RADIUS;
    asteroid->pos.z = (ASTEROID_SPAWN_RADIUS * sinf(temp)) * ARENA_RADIUS; 

    // Set the size of the asteroid.
    asteroid->size = rand() % (ASTEROID_MAX_SIZE + 1 - ASTEROID_MIN_SIZE) + ASTEROID_MIN_SIZE;

    // Set the velocity of the asteroid.
    asteroid->velocity = rand() % (ASTEROID_MAX_VELOCITY + 1 - ASTEROID_MIN_VELOCITY) + ASTEROID_MIN_VELOCITY;
    asteroid->velocity /= 1000;

    vec3d newVec = directionBetweenPoints(asteroid->pos, ship->pos);
    float length = PYTHAGORAS(newVec.x, newVec.y, newVec.z);

    asteroid->dir.x = (newVec.x / length);
    asteroid->dir.y = (newVec.y / length);
    asteroid->dir.z = (newVec.z / length);

    // Set to false since asteroids start outside the arena.
    asteroid->activated = false;

    // DEBUG: Since asteroids start as inactive, colour them red. 
    asteroid->r = 1;
    asteroid->g = 0;
    asteroid->b = 0;
}

void drawAsteroid(asteroid *asteroid) {
    glColor3f(asteroid->r, asteroid->g, asteroid->b);
    

    glPushMatrix();
    glTranslatef(asteroid->pos.x, asteroid->pos.y, asteroid->pos.z);
    glScalef(asteroid->size, asteroid->size, asteroid->size);
    glutSolidSphere(1.0, ASTEROID_DIVISIONS, ASTEROID_DIVISIONS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPopMatrix();

    // printf("asteroid->dir.x = %f\n", asteroid->dir.x);
    // printf("asteroid->dir.y = %f\n", asteroid->dir.y);
    // printf("asteroid->dir.z = %f\n", asteroid->dir.z);
}

void moveAsteroid(asteroid *asteroid, float deltaTime, int round) {
    vec3d result;

    result.x = asteroid->dir.x * (asteroid->velocity);
    result.y = asteroid->dir.y * (asteroid->velocity);
    result.z = asteroid->dir.z * (asteroid->velocity);

    result.x *= deltaTime;
    result.y *= deltaTime;
    result.z *= deltaTime;

    asteroid->pos.x += result.x;
    asteroid->pos.y += result.y;
    asteroid->pos.z += result.z;
}

bool asteroidWallCollision(asteroid *asteroid) {
    if(asteroid->activated) {
        asteroid->r = 1;
        asteroid->g = 1;
        asteroid->b = 1;
        if(asteroid->pos.x + asteroid->size >= ARENA_RADIUS || asteroid->pos.x - asteroid->size <= -ARENA_RADIUS) {
            asteroid->dir.x = -asteroid->dir.x;
            return true;
        }
        if(asteroid->pos.y + asteroid->size >= ARENA_RADIUS || asteroid->pos.y - asteroid->size <= -ARENA_RADIUS) {
            asteroid->dir.y = -asteroid->dir.y;
            return true;
        }
        if(asteroid->pos.z + asteroid->size >= ARENA_RADIUS || asteroid->pos.z - asteroid->size <= -ARENA_RADIUS) {
            asteroid->dir.z = -asteroid->dir.z;
            return true;
        } 
    } else {
        asteroid->r = 1;
        asteroid->g = 0;
        asteroid->b = 0;
    }
    return false;
}

void checkActivated(asteroid *asteroid) {
    // If the asteroid's x-position is inside the arena.
    if(asteroid->pos.x + asteroid->size <= ARENA_RADIUS && asteroid->pos.x + asteroid->size >= -ARENA_RADIUS) {
        // If the asteroid's y-position is inside the arena.
        if(asteroid->pos.x + asteroid->size <= ARENA_RADIUS && asteroid->pos.x + asteroid->size >= -ARENA_RADIUS) {
            // If the asteroid's z-position is inside the arena.
            if(asteroid->pos.x + asteroid->size <= ARENA_RADIUS && asteroid->pos.x + asteroid->size >= -ARENA_RADIUS) {
                // Activate the asteroid.
                asteroid->activated = true;
            }
        }       
    }
}