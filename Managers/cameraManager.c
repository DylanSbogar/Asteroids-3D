#include "cameraManager.h"

void initCamera(camera *camera) {
    camera->pos.x = 0;
    camera->pos.y = 0;
    camera->pos.z = 0;

    camera->front.x = 0;
    camera->front.y = 0;
    camera->front.z = 1;

    camera->up.x = 0;
    camera->up.y = 1;
    camera->up.z = 0;

    camera->velocity = SHIP_VELOCITY;

    camera->warpedCursor = false;

    camera->zoom = 15;
}
void moveCamera(camera *camera, float deltaTime, int turnValue, vec3d *ship) {
    camera->pos.x = ship->x - camera->zoom * cos(DEG_TO_RAD(camera->yaw));
    camera->pos.y = ship->y + (20 * -sin(DEG_TO_RAD(camera->pitch))) + 6;
    camera->pos.z = ship->z - camera->zoom * sin(DEG_TO_RAD(camera->yaw));
}