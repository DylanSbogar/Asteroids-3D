#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int screenWidth = 0;
int screenHeight = 0;

int currentTime = 0;
float previousTime = 0.0;
bool firstMouse = true;

keyHandler kh;
camera cam;
ship player;

void onReshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 1000.0);

    initCamera(&cam);
    initShip(&player);
}

void onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //TODO: Put draw methods here.
    placeCamera(&cam);
    drawAxes();
    drawArena();
    drawShip(&player);

    glutSwapBuffers();
    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("Error: %s\n", gluErrorString(err));
}

void onIdle() {
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = currentTime - previousTime;

    previousTime = currentTime;
    updateCameraPosition(&cam, &player);
    updateGameState(&cam, &player, deltaTime);
    glutPostRedisplay();
}

void updateGameState(camera *camera, ship *ship, float deltaTime) {
    if(kh.movingForward) {
        printf("FORWARD\n");
        camera->pos.z += MOVE_VELOCITY;
    }
    if(kh.movingBackward) {
        printf("BACKWARD\n");
        camera->pos.z -= MOVE_VELOCITY;
    }
    if(kh.turningLeft) {
        printf("LEFT\n");
        camera->pos.x += MOVE_VELOCITY;
    }
    if(kh.turningRight) {
        printf("RIGHT\n");
        camera->pos.x -= MOVE_VELOCITY;
    }
    if(kh.rollingLeft) {

    }
    if(kh.rollingRight) {

    }
    if(kh.restartGame) {
        initGame();
    }
}

void onKeyPress(unsigned char key, int x, int y) {
    switch(toupper(key)) {
        case 'W':
            kh.movingForward = true;
            kh.movingBackward = false;
            break;
        case 'A':
            kh.turningLeft = true;
            kh.turningRight = false;
            break;
        case 'S':
            kh.movingBackward = true;
            kh.movingForward = false;
            break;
        case 'D':
            kh.turningRight = true;
            kh.turningLeft = false;
            break;
        case 'Q':
            kh.rollingLeft = true;
            kh.rollingRight = false;
            break;
        case 'E':
            kh.rollingRight = true;
            kh.rollingLeft = false;
            break;
        case 'R':
            kh.restartGame = true;
            break;
        case KEY_ESC:
            exit(EXIT_SUCCESS);
            break;
    }
}
void onKeyUp(unsigned char key, int x, int y) {
    switch(toupper(key)) {
        case 'W':
            kh.movingForward = false;
            break;
        case 'A':
            kh.turningLeft = false;
            break;
        case 'S':
            kh.movingBackward = false;
            break;
        case 'D':
            kh.turningRight = false;
            break;
        case 'Q':
            kh.rollingLeft = false;
            break;
        case 'E':
            kh.rollingRight = false;
            break;
        case 'R':
            kh.restartGame = false;
            break;
    }
}

void onMousePress(int state, int button, int x, int y) {

}

// START INPUT METHODS
void onMouseMove(int x, int y) {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    if (firstMouse) {
        cam.lastX = x;
        cam.lastY = y;
        firstMouse = false;
    }
    // Everytime the cursor is warped, I do not want to perform any changes in the camera.
    if (cam.warpedCursor) {
        cam.lastX = x;
        cam.lastY = y;
        cam.warpedCursor = false;
    }

    float xOffset = (x - cam.lastX) * 0.1;
    float yOffset = (cam.lastY - y) * 0.1;
    cam.lastX = x;
    cam.lastY = y;

    cam.yaw += xOffset;
    cam.pitch += yOffset;

    int limit = 45;
    if (cam.pitch > limit) {
        cam.pitch = limit;
    } else if (cam.pitch < -limit) {
        cam.pitch = -limit;
    }

    int centerX = screenWidth / 2.0;
    int centerY = screenHeight / 2.0;
    if (x <= 10 || y <= 10 || x >= screenWidth - 10 || y >= screenHeight - 10) {
        cam.warpedCursor = true;
        CGPoint p = {(CGFloat) centerX, (CGFloat) centerY};
        CGWarpMouseCursorPosition(p);
    }
}
// END INPUT METHODS

void initKeyHandler() {
    kh.movingForward = false;
    kh.movingBackward = false;
    kh.turningLeft = false;
    kh.turningRight = false;
    kh.rollingLeft = false;
    kh.rollingRight = false;
    kh.restartGame = false;
}

void initGame() {
    initKeyHandler();

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Asteroids Arena 3D");
    glutFullScreen();

    glutReshapeFunc(onReshape);
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyUp);
    glutMouseFunc(onMousePress);
    glutPassiveMotionFunc(onMouseMove);
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onIdle);
    // glutSetCursor(GLUT_CURSOR_NONE);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    initGame();
    glutMainLoop();
    return(EXIT_SUCCESS);
}