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

void placeCamera(camera *camera) {
      gluLookAt(camera->pos.x, camera->pos.y, camera->pos.z,
            camera->pos.x + camera->front.x, camera->pos.y + camera->front.y, camera->pos.z + camera->front.z,
            0, 1, 0);
}

void updateCameraPosition(camera *camera, ship *ship) {

}