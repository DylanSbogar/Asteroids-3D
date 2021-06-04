#include "ship.h"

void initShipBody() {

}

void initShipTip() {
    
}

void initShipWings() {

}

void initShip(ship *ship) {
    ship->pos.x = 0;
    ship->pos.y = 0;
    ship->pos.z = 0;

    ship->dir.x = 0;
    ship->dir.y = 0;
    ship->dir.z = 0;

    // Set the ship velocity to be the same as the camera.
    ship->velocity = SHIP_VELOCITY;
}

void drawShip(ship *ship, float yaw, float roll, float pitch) {
    float matAmbient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
    float matDiffuse[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
    float matSpecular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
    float matShine[] = { 76.8f } ;

    // setup materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    // Draw the body.
    glPushMatrix();
        // glColor3f(1.0, 0.0, 1.0);
        glTranslatef(ship->pos.x, ship->pos.y, ship->pos.z);
        glRotatef(-yaw, 0, 1, 0);
        glRotatef(roll, 1, 0, 0);
        glRotatef(pitch, 0, 0, 1);
        glScalef(SHIP_LENGTH, SHIP_HEIGHT, SHIP_WIDTH);
        glutSolidCube(1.0);
    glPopMatrix();

    // Draw the collision debug sphere.
    // glPushMatrix();
    //     glColor3f(0.0, 0.0, 0.3);
    //     glTranslatef(ship->pos.x, ship->pos.y, ship->pos.z);
    //     glScalef(SHIP_LENGTH, SHIP_LENGTH, SHIP_LENGTH);
    //     glutWireSphere(1.0, 16, 16);
    // glPopMatrix();
}

void moveShip(ship *ship, float deltaTime, int turnValue) {
    ship->pos.x += turnValue * (deltaTime * (ship->velocity * ship->dir.x));
    ship->pos.y += turnValue * (deltaTime * (ship->velocity * ship->dir.y));
    ship->pos.z += turnValue * (deltaTime * (ship->velocity * ship->dir.z));
}