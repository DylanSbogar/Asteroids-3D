#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int screenWidth = 0;
int screenHeight = 0;

int roundNum = 0;

int currentTime = 0;
float previousTime = 0.0;

bool firstMouse = true;
bool gameOver = false;
bool roundOver;

keyHandler kh;
camera cam;
ship player;
// bullet testBullet;
bullet bullets[MAX_BULLETS];
asteroid asteroids[MAX_ROUNDS];

void placeCamera(camera *camera) {
    gluLookAt(camera->pos.x, camera->pos.y, camera->pos.z,
        player.pos.x + camera->front.x, player.pos.y + camera->front.y, player.pos.z + camera->front.z,
        0, 1, 0);
}

void onReshape(int w, int h) {
    glViewport(0, 0, w, h);

    screenWidth = w;
    screenHeight = h;

    const double aspectRatio = (double)w / (double)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, aspectRatio, 1.0, 2000.0);

    // Initialise the random number generator.
    time_t t;
    srand((unsigned) time(&t));

    initCamera(&cam);
    initShip(&player);

    for(int i = 0; i < roundNum; i++) {
        initAsteroid(&asteroids[i], &player);
    }
}

void initLighting() {
    float ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);
}

void renderFrame() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

     //TODO: Put draw methods here.
    placeCamera(&cam);
    shipWarning(&player);
    drawArena();
    // drawAxes();
    drawShip(&player, cam.yaw, cam.roll, cam.pitch);

    for(int i = 0; i < roundNum; i++) {
        if(asteroids[i].alive) {
            drawAsteroid(&asteroids[i]);
        }
    }

    for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i].activated) {
            drawBullet(&bullets[i]);
        }
    }
}

void updateCameraPosition(camera *camera, float deltaTime) {
    camera->pos.x = player.pos.x - 20 * cos(DEG_TO_RAD(camera->yaw));
    camera->pos.y = player.pos.y + 10;
    camera->pos.z = player.pos.z - 20 * sin(DEG_TO_RAD(camera->yaw));
}

void onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Handles all drawing functionality.
    renderFrame();

    glutSwapBuffers();

    // Check for errors.
    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("Error: %s\n", gluErrorString(err));
}

void onIdle() {
    // Calculate deltaTime.
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    // Perform idle checks for when the player is not moving (moving camera, asteroids)
    moveCamera(&cam, deltaTime, 1, &player.pos);
    updateGameState(&cam, &player, deltaTime);

    // Move all the asteroids.
    for(int i = 0; i < roundNum; i++) {
        if(asteroids[i].alive) {
            moveAsteroid(&asteroids[i], deltaTime, roundNum);
        }
    }
    glutPostRedisplay();
}

void updateGameState(camera *camera, ship *ship, float deltaTime) {
    if(kh.movingForward) {
        moveShip(&player, deltaTime, 1);
        moveCamera(&cam, deltaTime, 1, &ship->pos);
    }
    if(kh.movingBackward) {
        moveShip(&player, deltaTime, -1);
        moveCamera(&cam, deltaTime, -1, &ship->pos);
    }
    if(kh.restartGame) {
        initGame();
    }
    if(shipCollision(&player)) {
        initGame();
    }
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i].activated) {
            moveBullet(&bullets[i], deltaTime);
        }
        
        // Check if the bullet collides with the wall.
        bulletCollision(&bullets[i]);
    }

    // Used to calculate when the round ends.
    roundOver = true;

    for(int j = 0; j < roundNum; j++) {
        // 'Activate' asteroids as they enter the arena, and perform wall collision checks.
        checkActivated(&asteroids[j]);

        for(int d = 0; d < roundNum; d++) {
            if (d != j) {
                if(asteroids[d].alive) {
                    asteroidBouncing(&asteroids[j], &asteroids[d]);
                }
            }
        }

        // Check whether any of the asteroids are ready to bounce off the walls.
        asteroidWallCollision(&asteroids[j]);
        
        for(int k = 0; k < MAX_BULLETS; k++) {
            // Check whether a bullet has destroyed any of the asteroids.
            bulletAsteroidCollision(&bullets[k], &asteroids[j]);
        }
   
        // If the ship has collided with an asteroid, end the game.
        if(asteroidShipCollision(&player, &asteroids[j])) {
            // TODO: Replace with restartGame().
            initGame();
        }

        // If any asteroids are still alive, the round is not over.
        if(asteroids[j].alive) {
            roundOver = false;
        }
    }

    // If all asteroids are dead and the round is over.
    if(roundOver) {
        roundNum++;

        // TODO: Wait 5 seconds before starting the next wave.

        // Create x amount of new asteroids corresponding with the round number.
        for(int i = 0; i < roundNum; i++)
        {
            initAsteroid(&asteroids[i], &player);
        }
    }
}

void onKeyPress(unsigned char key, int x, int y) {
    switch(toupper(key)) {
        case 'W':
            kh.movingForward = true;
            kh.movingBackward = false;
            break;
        case 'A':
            kh.rollingLeft = true;
            kh.rollingRight = false;
            break;
        case 'S':
            kh.movingBackward = true;
            kh.movingForward = false;
            break;
        case 'D':
            kh.rollingRight = true;
            kh.rollingLeft = false;
            break;
        case 'R':
            gameOver = false;
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
            kh.rollingLeft = false;
            break;
        case 'S':
            kh.movingBackward = false;
            break;
        case 'D':
            kh.rollingRight = false;
            break;
        case 'R':
            gameOver = false;
            kh.restartGame = false;
            break;
    }
}

void onMousePress(int state, int button, int x, int y) {
    // If the left mouse button is pressed down.
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        bool fired = false;

        for(int i = 0; i < MAX_BULLETS; i++) {
            if(!bullets[i].activated && !fired) {
                initBullet(&bullets[i], &player);
                bullets[i].activated = true;
                fired = true;
            }
        }
    }
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

    // Set a limiter for the pitch of the camera.
    float limit = 62.5;
    if (cam.pitch > limit) {
        cam.pitch = limit;
    } else if (cam.pitch < -limit) {
        cam.pitch = -limit;
    }
    
    // Set the camera's direction (look) vector and normalise it.
    vec3d front;
    front.x = cos(DEG_TO_RAD(cam.yaw)) * cos(DEG_TO_RAD(cam.pitch));
    front.y = sin(DEG_TO_RAD(cam.pitch));
    front.z = sin(DEG_TO_RAD(cam.yaw)) * cos(DEG_TO_RAD(cam.pitch));
    cam.front = normalise(front);
    player.dir = normalise(front);


    // If the cursor reaches the edge of the screen, place it back in the center.
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
    kh.rollingLeft = false;
    kh.rollingRight = false;
    kh.restartGame = false;
}

void initGame() {
    // Set the roundNum number to 1.
    roundNum = 1;

    // Since the game is starting, set all keyHandler values to false.
    initKeyHandler();

    // Setting up the window.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Asteroids Arena 3D");
    glutFullScreen();

    // Various glut functions for gameplay.
    glutReshapeFunc(onReshape);
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyUp);
    glutMouseFunc(onMousePress);
    glutPassiveMotionFunc(onMouseMove);
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onIdle);

    initAsteroidVertices();
    initLighting();
    glEnable(GL_NORMALIZE);

    // Hide the cursor on screen.
    glutSetCursor(GLUT_CURSOR_NONE);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    initGame();
    glutMainLoop();
    return(EXIT_SUCCESS);
}