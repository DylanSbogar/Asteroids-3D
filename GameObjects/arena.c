#include "arena.h"



void drawAxes() {
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-10.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, -10.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, -10.0);
        glVertex3f(0.0, 0.0, 10.0);
    glEnd();
}

void drawWall(wall *wall) {
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(wall->x, wall->y, wall->z);
        if(wall->x != 0.0) glRotatef(90.0, 0.0, 1.0, 0.0);
        if(wall->y != 0.0) glRotatef(270.0, 1.0, 0.0, 0.0);
        glScalef(ARENA_RADIUS, ARENA_RADIUS, ARENA_RADIUS);
        glBegin(GL_LINES);
            float pos = -1.0;
            float inc = 2.0 / (float)WALL_SEGMENTS;

            for(int i = 0; i <= WALL_SEGMENTS; i++, pos+= inc) {
                glVertex3f(pos, -1.0, 0.0); glVertex3f(pos, 1.0, 0.0);
                glVertex3f(-1.0, pos, 0.0); glVertex3f(1.0, pos, 0.0);
            }
        glEnd();
    glPopMatrix();
}

void drawArena() {
    wall wallXPos;
    wallXPos.x = ARENA_RADIUS;
    wallXPos.y = 0;
    wallXPos.z = 0;

    wall wallXNeg;
    wallXNeg.x = -ARENA_RADIUS;
    wallXNeg.y = 0;
    wallXNeg.z = 0;

    wall wallYPos;
    wallYPos.x = 0;
    wallYPos.y = ARENA_RADIUS;
    wallYPos.z = 0;

    wall wallYNeg;
    wallYNeg.x = 0;
    wallYNeg.y = -ARENA_RADIUS;
    wallYNeg.z = 0;

    wall wallZPos;
    wallZPos.x = 0;
    wallZPos.y = 0;
    wallZPos.z = ARENA_RADIUS;

    wall wallZNeg;
    wallZNeg.x = 0;
    wallZNeg.y = 0;
    wallZNeg.z = -ARENA_RADIUS;

    drawWall(&wallXPos);
    drawWall(&wallXNeg);
    drawWall(&wallYPos);
    drawWall(&wallYNeg);
    drawWall(&wallZPos);
    drawWall(&wallZNeg);
}