#include "cameraManager.h"

void initCamera(camera *camera) {
    camera->pos.x = 0;
    camera->pos.y = 0;
    camera->pos.z = 0;

    camera->look.x = 0;
    camera->look.y = 0;
    camera->look.z = 10;

    camera->up.x = 0;
    camera->up.y = 1;
    camera->up.z = 0;

    camera->warpedCursor = false;
}

void placeCamera(camera *camera) {
    // gluLookAt(camera->pos.x, camera->pos.y, camera->pos.z,
    //           camera->look.x, camera->look.y, camera->look.z,
    //           camera->up.x, camera->up.y, camera->up.z);

      gluLookAt(camera->pos.x, camera->pos.y, camera->pos.z,
            camera->pos.x, camera->pos.y, camera->pos.z + 10,
            0, 1, 0);
}

void updateCameraPosition(camera *camera, ship *ship) {
    // camera->look.x = ship->pos.x + 50 * cos(camera->yaw * M_PI/180) * cos(camera->pitch * M_PI/180);
    // camera->look.y = ship->pos.y + (20 * sin(camera->pitch * M_PI/180)) - 10;
    // camera->look.z = ship->pos.z + 50 * sin(camera->yaw * M_PI/180) * cos(camera->pitch * M_PI/180);

    // camera->pos.x = ship->pos.x - 20 * cos(camera->yaw * M_PI/180);
    // camera->pos.y = ship->pos.y + 10;
    // camera->pos.z = ship->pos.z - 20 * sin(camera->yaw * M_PI/180);


}