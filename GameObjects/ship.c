#include "ship.h"

void initShip(ship *ship) {
    ship->pos.x = 0;
    ship->pos.y = 0;
    ship->pos.z = 0;

    ship->dir.x = 0;
    ship->dir.y = 0;
    ship->dir.z = 0;

    ship->velocity = 0.05;
}

void drawShip(ship *ship, float yaw, float roll, float pitch) {
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(ship->pos.x, ship->pos.y, ship->pos.z);
        glRotatef(-yaw, 0, 1, 0);
        glRotatef(roll, 1, 0, 0);
        glRotatef(pitch, 0, 0, 1);
        glScalef(6.0, 2.0, 4.0);
        glutWireCube(1.0);
    glPopMatrix();
}

void moveShip(ship *ship, float deltaTime, int turnValue) {
    ship->pos.x += turnValue * (deltaTime * (ship->velocity * ship->dir.x));
    ship->pos.y += turnValue * (deltaTime * (ship->velocity * ship->dir.y));
    ship->pos.z += turnValue * (deltaTime * (ship->velocity * ship->dir.z));
}