#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int screenWidth = 0;
int screenHeight = 0;

int currentTime = 0;
float previousTime = 0.0;

void onReshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 1000.0);
}

void onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    //TODO: Put draw methods here.

    glutSwapBuffers();
    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("Error: %s\n", gluErrorString(err));
}

void onIdle() {
    glutPostRedisplay();
}

void updateGameState() {

}

void initGame() {
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
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    initGame();
    glutMainLoop();
    return(EXIT_SUCCESS);
}



