#include "ship.h"

void initShip(ship *ship, camera *camera) {
    ship->pos.x = 0;
    ship->pos.y = 0;
    ship->pos.z = 0;

    ship->dir.x = 0;
    ship->dir.y = 0;
    ship->dir.z = 0;

    ship->velocity = 1;
}

void drawShip(ship *ship, camera *camera) {
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(camera->pos.x, camera->pos.y, camera->pos.z);
        glRotatef(-camera->yaw, 0, 1, 0);
        glRotatef(camera->roll, 1, 0, 0);
        glRotatef(camera->pitch, 0, 0, 1);
        glTranslatef(15,-3,0);
        glScalef(6.0, 2.0, 2.0);
        glutWireCube(1.0);
    glPopMatrix();
}

void moveShip(ship *ship, float deltaTime, camera *camera) {
    ship->pos.x = camera->pos.x + 15;
    ship->pos.y = camera->pos.y - 3;
    ship->pos.z = camera->pos.z;

    // printf("ship->pos.x = %f\n", ship->pos.x);
    // printf("ship->pos.y = %f\n", ship->pos.y);
    // printf("ship->pos.z = %f\n", ship->pos.z);
}