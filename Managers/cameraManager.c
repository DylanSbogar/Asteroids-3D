#include "cameraManager.h"

void initCamera(camera *camera) {
    camera->pos.x = 0;
    camera->pos.y = 0;
    camera->pos.z = 0;

    camera->front.x = 0;
    camera->front.y = 0;
    camera->front.z = -1;

    camera->up.x = 0;
    camera->up.y = 1;
    camera->up.z = 0;

    camera->velocity = SHIP_VELOCITY;

    camera->warpedCursor = false;
}
void moveCamera(camera *camera, float deltaTime, int turnValue, vec3d *ship) {
    camera->pos.x = ship->x - 15 * cos(DEG_TO_RAD(camera->yaw));
    camera->pos.y = ship->y + 3;
    camera->pos.z = ship->z - 15 * sin(DEG_TO_RAD(camera->yaw));
}