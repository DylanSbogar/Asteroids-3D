#include "bullet.h"

void initBullet(bullet *bullet, ship *ship, camera *camera) {
    // Set up the bullet.
    bullet->pos.x = ship->pos.x;
    bullet->pos.y = ship->pos.y;
    bullet->pos.z = ship->pos.z;

    bullet->dir.x = camera->pos.x + camera->front.x;
    bullet->dir.y = camera->pos.y + camera->front.y;
    bullet->dir.z = camera->pos.z + camera->front.z;

    bullet->velocity = 1;

    bullet->activated = false;
}

void moveBullet(bullet *bullet, float deltaTime) {
    vec3d result;

    result.x = bullet->dir.x * (bullet->velocity);
    result.y = bullet->dir.y * (bullet->velocity);
    result.z = bullet->dir.z * (bullet->velocity);

    result.x *= deltaTime;
    result.y *= deltaTime;
    result.z *= deltaTime;

    bullet->pos.x += result.x;
    bullet->pos.y += result.y;
    bullet->pos.z += result.z;
}

