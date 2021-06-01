#include "bullet.h"

void initBullet(bullet *bullet, ship *ship, camera *camera) {
    // Set up the bullet.
    bullet->pos.x = ship->pos.x;
    bullet->pos.y = ship->pos.y;
    bullet->pos.z = ship->pos.z;

    bullet->dir.x = camera->pos.x + camera->front.x;
    bullet->dir.y = camera->pos.y + camera->front.y;
    bullet->dir.z = camera->pos.z + camera->front.z;

    bullet->velocity = 0.05;

    bullet->activated = false;
}

void drawBullet(bullet *bullet) {
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(bullet->pos.x, bullet->pos.y, bullet->pos.z);
        glScalef(0.5, 0.5, 0.5);
        glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void moveBullet(bullet *bullet, float deltaTime, vec3d dir) {
    vec3d result;

    result.x = dir.x * (bullet->velocity);
    result.y = dir.y * (bullet->velocity);
    result.z = dir.z * (bullet->velocity);

    result.x *= deltaTime;
    result.y *= deltaTime;
    result.z *= deltaTime;

    bullet->pos.x += result.x;
    bullet->pos.y += result.y;
    bullet->pos.z += result.z;
}

