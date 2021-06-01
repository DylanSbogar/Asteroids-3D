#include "bullet.h"

void initBullet(bullet *bullet) {
    // Set up the bullet.
    bullet->pos.x = 0;
    bullet->pos.y = 0;
    bullet->pos.z = 0;

    bullet->dir.x = 0;
    bullet->dir.y = 0;
    bullet->dir.z = -1;

    // Have the bullet's velocity be 50% faster than the ship's velocity.
    bullet->velocity = 0.075;

    bullet->activated = false;
}

void drawBullet(bullet *bullet) {
    // Draw a glutSolidSphere at the bullet's current position, and scale.
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(bullet->pos.x, bullet->pos.y, bullet->pos.z);
        glScalef(0.5, 0.5, 0.5);
        glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void moveBullet(bullet *bullet, float deltaTime, vec3d dir) {
    // Calculate the bullet's next position.
    bullet->pos.x += deltaTime * (bullet->velocity * dir.x);
    bullet->pos.y += deltaTime * (bullet->velocity * dir.y);
    bullet->pos.z += deltaTime * (bullet->velocity * dir.z);
}