#include "bullet.h"

void initBullet(bullet *bullet, ship *ship) {
    // Set up the bullet.
    bullet->pos.x = ship->pos.x;
    bullet->pos.y = ship->pos.y;
    bullet->pos.z = ship->pos.z;

    bullet->dir.x = ship->dir.x;
    bullet->dir.y = ship->dir.y;
    bullet->dir.z = ship->dir.z;

    // Have the bullet's velocity be 50% faster than the ship's velocity.
    bullet->velocity = SHIP_VELOCITY * 1.5;

    bullet->size = BULLET_RADIUS;
    bullet->activated = false;

    bullet->r = 0;
    bullet->g = 1;
    bullet->b = 0;
}

void drawBullet(bullet *bullet) {
    // Draw a glutSolidSphere at the bullet's current position, and scale.
    glPushMatrix();
        glColor3f(bullet->r, bullet->g, bullet->b);
        glTranslatef(bullet->pos.x, bullet->pos.y, bullet->pos.z);
        glScalef(bullet->size, bullet->size, bullet->size);
        glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void moveBullet(bullet *bullet, float deltaTime) {
    // Calculate the bullet's next position.
    bullet->pos.x += deltaTime * (bullet->velocity * bullet->dir.x);
    bullet->pos.y += deltaTime * (bullet->velocity * bullet->dir.y);
    bullet->pos.z += deltaTime * (bullet->velocity * bullet->dir.z);
}

void bulletCollision(bullet *bullet) {
    if(bullet->activated) {
        bullet->r = 0;
        bullet->g = 1;
        bullet->b = 0;
        if(bullet->pos.x + bullet->size >= ARENA_RADIUS || bullet->pos.x - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
            // bullet->dir.x = -bullet->dir.x; // bounce
        }
        if(bullet->pos.y + bullet->size >= ARENA_RADIUS || bullet->pos.y - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
            // bullet->dir.y = -bullet->dir.y; // bounce
        }
        if(bullet->pos.z + bullet->size >= ARENA_RADIUS || bullet->pos.z - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
            // bullet->dir.z = -bullet->dir.z; // bounce
        } 
    } else {
        bullet->r = 1;
        bullet->g = 1;
        bullet->b = 1;
    }
}

void bulletAsteroidCollision(bullet *bullet, asteroid *asteroid) {
    // Get the distance between the bullet and the asteroid.
    vec3d result = distanceBetweenPoints(bullet->pos, asteroid->pos);
    float length = PYTHAGORAS(result.x, result.y, result.z);

    if(length < asteroid->size + SHIP_LENGTH) {
        asteroid->velocity = 0;
        asteroid->r = 0, asteroid->g = 0, asteroid->b = 1;
        bullet->activated = false;
    }
}