#include "arena.h"

float wallNormal[] = {0.3, 0.3, 0.3};
float wallWarning[] = {0.3, 0.0, 0.0};

void drawAxes() {
    glPushMatrix();
    glScalef(ARENA_RADIUS, ARENA_RADIUS, ARENA_RADIUS);
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glPopMatrix();
}

void initWall(wall *wall) {

}

void drawWall(wall *wall) {
    // glColor3f(0.3, 0.0, 0.0);
    glPushMatrix(); 
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(wall->pos.x, wall->pos.y, wall->pos.z);
        if(wall->pos.x != 0.0) glRotatef(90.0, 0.0, 1.0, 0.0);
        if(wall->pos.y != 0.0) glRotatef(270.0, 1.0, 0.0, 0.0);
        glScalef(ARENA_RADIUS, ARENA_RADIUS, ARENA_RADIUS);
        glBegin(GL_LINES);
            float position = -1.0;
            float increment = 2.0 / (float)WALL_SEGMENTS;

            for(int i = 0; i <= WALL_SEGMENTS; i++, position+= increment) {
                glVertex3f(position, -1.0, 0.0); glVertex3f(position, 1.0, 0.0);
                glVertex3f(-1.0, position, 0.0); glVertex3f(1.0, position, 0.0);
            }
        glEnd();
    glPopMatrix();
}

void drawArena() {
    // Set up co-ordinates for the wall at X+ and draw.
    wall wallXPos;
    wallXPos.pos = (vec3d) {ARENA_RADIUS,0,0};
    drawWall(&wallXPos);

    // Set up co-ordinates for the wall at X- and draw.
    wall wallXNeg;
    wallXNeg.pos = (vec3d) {-ARENA_RADIUS, 0, 0};
    drawWall(&wallXNeg);

    // Set up co-ordinates for the wall at Y+ and draw.
    wall wallYPos;
    wallYPos.pos = (vec3d) {0, ARENA_RADIUS, 0};
    drawWall(&wallYPos);

    // Set up co-ordinates for the wall at Y- and draw.
    wall wallYNeg;
    wallYNeg.pos = (vec3d) {0, -ARENA_RADIUS, 0};
    drawWall(&wallYNeg);

    // Set up co-ordinates for the wall at Z+ and draw.
    wall wallZPos;
    wallZPos.pos = (vec3d) {0, 0, ARENA_RADIUS};
    drawWall(&wallZPos);

    // Set up co-ordinates for the wall at Z- and draw.
    wall wallZNeg;
    wallZNeg.pos = (vec3d) {0, 0, -ARENA_RADIUS};
    drawWall(&wallZNeg);
}

// TODO: Change 6, 2 and 2 with ships length, width and height (roughly)
bool shipWarning(ship *ship) {
    if(ship->pos.x + (6 * SHIP_WARNING) >= ARENA_RADIUS || ship->pos.x + (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        printf("ship->pos.x = %f\n", ship->pos.x);
        printf("ship->pos.y = %f\n", ship->pos.y);
        printf("ship->pos.z = %f\n", ship->pos.z);
        return true;
    }

    if(ship->pos.y + (6 * SHIP_WARNING) >= ARENA_RADIUS || ship->pos.y + (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        printf("ship->pos.x = %f\n", ship->pos.x);
        printf("ship->pos.y = %f\n", ship->pos.y);
        printf("ship->pos.z = %f\n", ship->pos.z);
        return true;
    }

    if(ship->pos.z + (6 * SHIP_WARNING) >= ARENA_RADIUS || ship->pos.z + (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        printf("ship->pos.x = %f\n", ship->pos.x);
        printf("ship->pos.y = %f\n", ship->pos.y);
        printf("ship->pos.z = %f\n", ship->pos.z);
        return true;
    } 
    if(ship->pos.x - (6 * SHIP_WARNING) >= ARENA_RADIUS || ship->pos.x - (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        printf("ship->pos.x = %f\n", ship->pos.x);
        printf("ship->pos.y = %f\n", ship->pos.y);
        printf("ship->pos.z = %f\n", ship->pos.z);
        return true;
    }

    if(ship->pos.y - (6 * SHIP_WARNING) >= ARENA_RADIUS || ship->pos.y - (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        printf("ship->pos.x = %f\n", ship->pos.x);
        printf("ship->pos.y = %f\n", ship->pos.y);
        printf("ship->pos.z = %f\n", ship->pos.z);
        return true;
    }

    if(ship->pos.z - (6 * SHIP_WARNING) >= ARENA_RADIUS || ship->pos.z - (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        printf("ship->pos.x = %f\n", ship->pos.x);
        printf("ship->pos.y = %f\n", ship->pos.y);
        printf("ship->pos.z = %f\n", ship->pos.z);
        return true;
    } 
    return false;
}

// TODO: Change 6, 2 and 2 with ships length, width and height (roughly)
bool shipCollision(ship *ship) {
    if(ship->pos.x + (6 * SHIP_COLLISION) >= ARENA_RADIUS || ship->pos.x + (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        return true;
    }

    if(ship->pos.y + (6 * SHIP_COLLISION) >= ARENA_RADIUS || ship->pos.y + (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        return true;
    }

    if(ship->pos.z + (6 * SHIP_COLLISION) >= ARENA_RADIUS || ship->pos.z + (6 * SHIP_COLLISION) <= -ARENA_RADIUS ) {
        return true;
    } else {
        return false;
    }
}