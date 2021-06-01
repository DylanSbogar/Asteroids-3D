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

void drawWall(wall *wall, float *colour) {
    // glColor3f(0.3, 0.0, 0.0);
    glPushMatrix(); 
        glColor3f(colour[0], colour[1], colour[2]);
        // glColor3f(0.2, 0.2, 0.2);
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

wall initArena() {
    wall temp;

    return temp;
}

void drawArena() {
    // Set up co-ordinates for the wall at X+ and draw.
    wall wallXPos;
    wallXPos.pos = (vec3d) {ARENA_RADIUS,0,0};
    drawWall(&wallXPos, wallNormal);

    // Set up co-ordinates for the wall at X- and draw.
    wall wallXNeg;
    wallXNeg.pos = (vec3d) {-ARENA_RADIUS, 0, 0};
    drawWall(&wallXNeg, wallNormal);

    // Set up co-ordinates for the wall at Y+ and draw.
    wall wallYPos;
    wallYPos.pos = (vec3d) {0, ARENA_RADIUS, 0};
    drawWall(&wallYPos, wallNormal);

    // Set up co-ordinates for the wall at Y- and draw.
    wall wallYNeg;
    wallYNeg.pos = (vec3d) {0, -ARENA_RADIUS, 0};
    drawWall(&wallYNeg, wallNormal);

    // Set up co-ordinates for the wall at Z+ and draw.
    wall wallZPos;
    wallZPos.pos = (vec3d) {0, 0, ARENA_RADIUS};
    drawWall(&wallZPos, wallNormal);

    // Set up co-ordinates for the wall at Z- and draw.
    wall wallZNeg;
    wallZNeg.pos = (vec3d) {0, 0, -ARENA_RADIUS};
    drawWall(&wallZNeg, wallNormal);
}

void shipWarning(ship *ship) {
    wall wallXPos;
    wallXPos.pos = (vec3d) {ARENA_RADIUS,0,0};

    wall wallXNeg;
    wallXNeg.pos = (vec3d) {-ARENA_RADIUS, 0, 0};

    wall wallYPos;
    wallYPos.pos = (vec3d) {0, ARENA_RADIUS, 0};

    wall wallYNeg;
    wallYNeg.pos = (vec3d) {0, -ARENA_RADIUS, 0};

    wall wallZPos;
    wallZPos.pos = (vec3d) {0, 0, ARENA_RADIUS};

    wall wallZNeg;
    wallZNeg.pos = (vec3d) {0, 0, -ARENA_RADIUS};

    // X Walls
    if (ship->pos.x + (SHIP_LENGTH * SHIP_WARNING) >  ARENA_RADIUS) {
        drawWall(&wallXPos, wallWarning);
    } else if (ship->pos.x - (SHIP_LENGTH * SHIP_WARNING) < -ARENA_RADIUS) {
        drawWall(&wallXNeg, wallWarning);
    }
    // Y Walls
    if (ship->pos.y + (SHIP_LENGTH * SHIP_WARNING) > ARENA_RADIUS) {
        drawWall(&wallYPos, wallWarning);
    } else if (ship->pos.y - (SHIP_LENGTH * SHIP_WARNING) < -ARENA_RADIUS) {
        drawWall(&wallYNeg, wallWarning);
    }
    // Z Walls
    if (ship->pos.z + (SHIP_LENGTH * SHIP_WARNING) > ARENA_RADIUS) {
        drawWall(&wallZPos, wallWarning);
    } else if (ship->pos.z - (SHIP_LENGTH * SHIP_WARNING) < -ARENA_RADIUS) {
        drawWall(&wallZNeg, wallWarning);
    }

}

bool shipCollision(ship *ship) {
    // Check if the ship has collided with a wall on the X-Axis.
    if(ship->pos.x + (SHIP_LENGTH) >= ARENA_RADIUS || ship->pos.x + (SHIP_LENGTH) <= -ARENA_RADIUS ) {
        return true;
    }

    // Check if the ship has collided with a wall on the Y-Axis.
    if(ship->pos.y + (SHIP_LENGTH) >= ARENA_RADIUS || ship->pos.y + (SHIP_LENGTH) <= -ARENA_RADIUS ) {
        return true;
    }

    // Check if the ship has collided with a wall on the Z-Axis.
    if(ship->pos.z + (SHIP_LENGTH) >= ARENA_RADIUS || ship->pos.z + (SHIP_LENGTH) <= -ARENA_RADIUS ) {
        return true;
    }
    return false;
}