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
    // Draw the body.
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(ship->pos.x, ship->pos.y, ship->pos.z);
        glRotatef(-yaw, 0, 1, 0);
        glRotatef(roll, 1, 0, 0);
        glRotatef(pitch, 0, 0, 1);
        glScalef(SHIP_LENGTH, SHIP_HEIGHT, SHIP_WIDTH);
        glutWireCube(1.0);
    glPopMatrix();

    // Draw the collision debug sphere.
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.3);
        glTranslatef(ship->pos.x, ship->pos.y, ship->pos.z);
        glScalef(SHIP_LENGTH, SHIP_LENGTH, SHIP_LENGTH);
        glutWireSphere(1.0, 16, 16);
    glPopMatrix();

    // Draw the warning debug sphere.
    glPushMatrix();
        glColor3f(0.3, 0.0, 0.3);
        glTranslatef(ship->pos.x, ship->pos.y, ship->pos.z);
        glScalef(SHIP_LENGTH * SHIP_WARNING, SHIP_LENGTH * SHIP_WARNING, SHIP_LENGTH * SHIP_WARNING);
        glutWireSphere(1.0, 16, 16);
    glPopMatrix();
}

void moveShip(ship *ship, float deltaTime, int turnValue) {
    ship->pos.x += turnValue * (deltaTime * (ship->velocity * ship->dir.x));
    ship->pos.y += turnValue * (deltaTime * (ship->velocity * ship->dir.y));
    ship->pos.z += turnValue * (deltaTime * (ship->velocity * ship->dir.z));
}