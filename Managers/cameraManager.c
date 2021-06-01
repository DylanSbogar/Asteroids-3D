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

    camera->velocity = 0.05;

    camera->warpedCursor = false;
}

// void placeCamera(camera *camera) {
//       gluLookAt(camera->pos.x, camera->pos.y, camera->pos.z,
//             camera->pos.x + camera->front.x, camera->pos.y + camera->front.y, camera->pos.z + camera->front.z,
//             0, 1, 0);
// }

void moveCamera(camera *camera, float deltaTime, int turnValue, vec3d *ship) {
    // camera->pos.x += turnValue * (deltaTime * (camera->velocity * camera->front.x));
    // camera->pos.y += turnValue * (deltaTime * (camera->velocity * camera->front.y));
    // camera->pos.z += turnValue * (deltaTime * (camera->velocity * camera->front.z));

        camera->pos.x = ship->x - 15 * cos(camera->yaw * M_PI/180);
    camera->pos.y = ship->y + 3;
    camera->pos.z = ship->z - 15 * sin(camera->yaw * M_PI/180);
}