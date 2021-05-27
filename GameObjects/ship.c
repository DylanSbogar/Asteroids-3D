#include "ship.h"

void initShip(ship *ship) {
    ship->pos.x = 0;
    ship->pos.y = 0;
    ship->pos.z = 0;

    ship->dir.x = 1;
    ship->dir.y = 0;
    ship->dir.z = 0;

    ship->velocity = 1;
}

void drawShip(ship *ship) {
    
}

void moveShip(ship *ship, float deltaTime) {

}

void rotateShip(ship *ship, int turnValue, float deltaTime) {

}