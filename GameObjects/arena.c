#include "arena.h"

float wallNormal[] = {0.1, 0.1, 0.1};
float wallWarning[] = {0.3, 0.0, 0.0};

vec3d skyboxRightVertices[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
vec3d skyboxLeftVertices[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
vec3d skyboxFrontVertices[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
vec3d skyboxBackVertices[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
vec3d skyboxTopVertices[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
vec3d skyboxBottomVertices[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];

texCoord skyboxRightTexcoords[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
texCoord skyboxLeftTexcoords[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
texCoord skyboxFrontTexcoords[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
texCoord skyboxBackTexcoords[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
texCoord skyboxTopTexcoords[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];
texCoord skyboxBottomTexcoords[SKYBOX_SEGMENTS + 1][SKYBOX_SEGMENTS + 1];

GLuint skyboxRight;
GLuint skyboxLeft;
GLuint skyboxFront;
GLuint skyboxBack;
GLuint skyboxTop;
GLuint skyboxBottom;

void initSkyboxTexcoords() {
    float tu_delta = 1.0/(float)(SKYBOX_SEGMENTS);
    float tv_delta = 1.0/(float)(SKYBOX_SEGMENTS);

    float tv = 1.0;                                   // start at 1.0 in v direction and subtract delta for each row
    for (int row = 0; row <= SKYBOX_SEGMENTS; row++, tv -= tv_delta) {
        float tu = 0.0;                                 // start at 0.0 in u direction and add delta for each column
        for (int col = 0; col <= SKYBOX_SEGMENTS; col++, tu += tu_delta) {
        skyboxRightTexcoords[row][col].u = tu;
        skyboxRightTexcoords[row][col].v = tv;

        skyboxLeftTexcoords[row][col].u = tu;
        skyboxLeftTexcoords[row][col].v = tv;

        skyboxFrontTexcoords[row][col].u = tu;
        skyboxFrontTexcoords[row][col].v = tv;

        skyboxBackTexcoords[row][col].u = tu;
        skyboxBackTexcoords[row][col].v = tv;

        skyboxTopTexcoords[row][col].u = tu;
        skyboxTopTexcoords[row][col].v = tv;

        skyboxBottomTexcoords[row][col].u = tu;
        skyboxBottomTexcoords[row][col].v = tv;
        }
    }
}

void initSkyboxVertices() {
    int x_min = -1;
    int x_max = 1;
    int y_min = -1;
    int y_max = 1;

    // calculate distance between each vertex
    float x_step = (x_max - x_min) / (float)SKYBOX_SEGMENTS;
    float y_step = (y_max - y_min) / (float)SKYBOX_SEGMENTS;
    vec3d vertex;

    // fill the array of vertices
    vertex.z = 0;
    for (int row=0; row <= SKYBOX_SEGMENTS; row++) {
        vertex.y = y_min + row * y_step;
        for (int col=0; col <= SKYBOX_SEGMENTS; col++) {
            vertex.x = x_min + col * x_step;
            skyboxRightVertices[row][col] = vertex;
            skyboxLeftVertices[row][col] = vertex;
            skyboxFrontVertices[row][col] = vertex;
            skyboxBackVertices[row][col] = vertex;
            skyboxTopVertices[row][col] = vertex;
            skyboxBottomVertices[row][col] = vertex;
        }
    }
}

void initSkyboxTextures() {
    int width, height, components;
    unsigned char *data, *data2, *data3, *data4, *data5, *data6;

    data = stbi_load("GameObjects/Assets/skybox/right.png", &width, &height, &components, STBI_rgb);
    glPushAttrib(GL_TEXTURE_BIT);
    glGenTextures(1, &skyboxRight);
    glBindTexture(GL_TEXTURE_2D, skyboxRight);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
    glPopAttrib();

        data2 = stbi_load("GameObjects/Assets/skybox/left.png", &width, &height, &components, STBI_rgb);
    glPushAttrib(GL_TEXTURE_BIT);
    glGenTextures(1, &skyboxLeft);
    glBindTexture(GL_TEXTURE_2D, skyboxLeft);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
    free(data2);
    glPopAttrib();

        data3 = stbi_load("GameObjects/Assets/skybox/front.png", &width, &height, &components, STBI_rgb);
    glPushAttrib(GL_TEXTURE_BIT);
    glGenTextures(1, &skyboxFront);
    glBindTexture(GL_TEXTURE_2D, skyboxFront);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
    free(data3);
    glPopAttrib();

        data4 = stbi_load("GameObjects/Assets/skybox/back.png", &width, &height, &components, STBI_rgb);
    glPushAttrib(GL_TEXTURE_BIT);
    glGenTextures(1, &skyboxBack);
    glBindTexture(GL_TEXTURE_2D, skyboxBack);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
    free(data4);
    glPopAttrib();

        data5 = stbi_load("GameObjects/Assets/skybox/top.png", &width, &height, &components, STBI_rgb);
    glPushAttrib(GL_TEXTURE_BIT);
    glGenTextures(1, &skyboxTop);
    glBindTexture(GL_TEXTURE_2D, skyboxTop);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
    free(data5);
    glPopAttrib();

        data6 = stbi_load("GameObjects/Assets/skybox/bottom.png", &width, &height, &components, STBI_rgb);
    glPushAttrib(GL_TEXTURE_BIT);
    glGenTextures(1, &skyboxBottom);
    glBindTexture(GL_TEXTURE_2D, skyboxBottom);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);
    free(data6);
    glPopAttrib();
}

void drawSkybox(camera *camera) {
    glDisable(GL_LIGHTING);
    float matAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
    float matDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    float matShininess[] = { 100.0 };

    glEnable(GL_TEXTURE_2D);

    // setup materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    // Right wall XPOS
    glBindTexture(GL_TEXTURE_2D, skyboxRight);
    glPushMatrix();
    glTranslatef(camera->pos.x + 1, camera->pos.y, camera->pos.z);
    glRotatef(270, 0.0, 1.0, 0.0);
    glRotatef(180, 0, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    for (int row=0; row<SKYBOX_SEGMENTS; row++) {
        for (int col=0; col<SKYBOX_SEGMENTS; col++) {
        glTexCoord2f(skyboxRightTexcoords[row][col].u, skyboxRightTexcoords[row][col].v);
        glVertex3f(skyboxRightVertices[row][col].x,    skyboxRightVertices[row][col].y,     skyboxRightVertices[row][col].z);

        glTexCoord2f(skyboxRightTexcoords[row][col+1].u, skyboxRightTexcoords[row][col+1].v);
        glVertex3f(skyboxRightVertices[row][col+1].x,    skyboxRightVertices[row][col+1].y,   skyboxRightVertices[row][col+1].z);

        glTexCoord2f(skyboxRightTexcoords[row+1][col+1].u, skyboxRightTexcoords[row+1][col+1].v);
        glVertex3f(skyboxRightVertices[row+1][col+1].x,    skyboxRightVertices[row+1][col+1].y, skyboxRightVertices[row+1][col+1].z);

        glTexCoord2f(skyboxRightTexcoords[row+1][col].u, skyboxRightTexcoords[row+1][col].v);
        glVertex3f(skyboxRightVertices[row+1][col].x,    skyboxRightVertices[row+1][col].y,   skyboxRightVertices[row+1][col].z);
        }
    }
    glEnd();
    glPopMatrix();

    // Left wall XNEG
    glBindTexture(GL_TEXTURE_2D, skyboxLeft);
    glPushMatrix();
    glTranslatef(camera->pos.x - 1, camera->pos.y, camera->pos.z);
    glRotatef(270, 0.0, 1.0, 0.0);
    glBegin(
        GL_QUADS);
    glNormal3f(0, 0, 1);
    for (int row=0; row<SKYBOX_SEGMENTS; row++) {
        for (int col=0; col<SKYBOX_SEGMENTS; col++) {
        glTexCoord2f(skyboxLeftTexcoords[row][col].u, skyboxLeftTexcoords[row][col].v);
        glVertex3f(skyboxLeftVertices[row][col].x,    skyboxLeftVertices[row][col].y,     skyboxLeftVertices[row][col].z);

        glTexCoord2f(skyboxLeftTexcoords[row][col+1].u, skyboxLeftTexcoords[row][col+1].v);
        glVertex3f(skyboxLeftVertices[row][col+1].x,    skyboxLeftVertices[row][col+1].y,   skyboxLeftVertices[row][col+1].z);

        glTexCoord2f(skyboxLeftTexcoords[row+1][col+1].u, skyboxLeftTexcoords[row+1][col+1].v);
        glVertex3f(skyboxLeftVertices[row+1][col+1].x,    skyboxLeftVertices[row+1][col+1].y, skyboxLeftVertices[row+1][col+1].z);

        glTexCoord2f(skyboxLeftTexcoords[row+1][col].u, skyboxLeftTexcoords[row+1][col].v);
        glVertex3f(skyboxLeftVertices[row+1][col].x,    skyboxLeftVertices[row+1][col].y,   skyboxLeftVertices[row+1][col].z);
        }
    }
    glEnd();
    glPopMatrix();

    // FRONT WALL ZPOS
    glBindTexture(GL_TEXTURE_2D, skyboxFront);
    glPushMatrix();
    glTranslatef(camera->pos.x, camera->pos.y, camera->pos.z + 1);
    glBegin(
        GL_QUADS);
    glNormal3f(0, 0, 1);
    for (int row=0; row<SKYBOX_SEGMENTS; row++) {
        for (int col=0; col<SKYBOX_SEGMENTS; col++) {
        glTexCoord2f(skyboxFrontTexcoords[row][col].u, skyboxFrontTexcoords[row][col].v);
        glVertex3f(skyboxFrontVertices[row][col].x,    skyboxFrontVertices[row][col].y,     skyboxFrontVertices[row][col].z);

        glTexCoord2f(skyboxFrontTexcoords[row][col+1].u, skyboxFrontTexcoords[row][col+1].v);
        glVertex3f(skyboxFrontVertices[row][col+1].x,    skyboxFrontVertices[row][col+1].y,   skyboxFrontVertices[row][col+1].z);

        glTexCoord2f(skyboxFrontTexcoords[row+1][col+1].u, skyboxFrontTexcoords[row+1][col+1].v);
        glVertex3f(skyboxFrontVertices[row+1][col+1].x,    skyboxFrontVertices[row+1][col+1].y, skyboxFrontVertices[row+1][col+1].z);

        glTexCoord2f(skyboxFrontTexcoords[row+1][col].u, skyboxFrontTexcoords[row+1][col].v);
        glVertex3f(skyboxFrontVertices[row+1][col].x,    skyboxFrontVertices[row+1][col].y,   skyboxFrontVertices[row+1][col].z);
        }
    }
    glEnd();
    glPopMatrix();

    // BACK WALL ZNEG
    glBindTexture(GL_TEXTURE_2D, skyboxBack);
    glPushMatrix();
    glTranslatef(camera->pos.x, camera->pos.y, camera->pos.z - 1);
    glRotatef(180, 0, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    for (int row=0; row<SKYBOX_SEGMENTS; row++) {
        for (int col=0; col<SKYBOX_SEGMENTS; col++) {
        glTexCoord2f(skyboxBackTexcoords[row][col].u, skyboxBackTexcoords[row][col].v);
        glVertex3f(skyboxBackVertices[row][col].x,    skyboxBackVertices[row][col].y,     skyboxBackVertices[row][col].z);

        glTexCoord2f(skyboxBackTexcoords[row][col+1].u, skyboxBackTexcoords[row][col+1].v);
        glVertex3f(skyboxBackVertices[row][col+1].x,    skyboxBackVertices[row][col+1].y,   skyboxBackVertices[row][col+1].z);

        glTexCoord2f(skyboxBackTexcoords[row+1][col+1].u, skyboxBackTexcoords[row+1][col+1].v);
        glVertex3f(skyboxBackVertices[row+1][col+1].x,    skyboxBackVertices[row+1][col+1].y, skyboxBackVertices[row+1][col+1].z);

        glTexCoord2f(skyboxBackTexcoords[row+1][col].u, skyboxBackTexcoords[row+1][col].v);
        glVertex3f(skyboxBackVertices[row+1][col].x,    skyboxBackVertices[row+1][col].y,   skyboxBackVertices[row+1][col].z);
        }
    }
    glEnd();
    glPopMatrix();

    // TOP WALL YPOS
    glBindTexture(GL_TEXTURE_2D, skyboxTop);
    glPushMatrix();
    glTranslatef(camera->pos.x, camera->pos.y + 1, camera->pos.z);
    glRotatef(270, 1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    for (int row=0; row<SKYBOX_SEGMENTS; row++) {
        for (int col=0; col<SKYBOX_SEGMENTS; col++) {
        glTexCoord2f(skyboxTopTexcoords[row][col].u, skyboxTopTexcoords[row][col].v);
        glVertex3f(skyboxTopVertices[row][col].x,    skyboxTopVertices[row][col].y,     skyboxTopVertices[row][col].z);

        glTexCoord2f(skyboxTopTexcoords[row][col+1].u, skyboxTopTexcoords[row][col+1].v);
        glVertex3f(skyboxTopVertices[row][col+1].x,    skyboxTopVertices[row][col+1].y,   skyboxTopVertices[row][col+1].z);

        glTexCoord2f(skyboxTopTexcoords[row+1][col+1].u, skyboxTopTexcoords[row+1][col+1].v);
        glVertex3f(skyboxTopVertices[row+1][col+1].x,    skyboxTopVertices[row+1][col+1].y, skyboxTopVertices[row+1][col+1].z);

        glTexCoord2f(skyboxTopTexcoords[row+1][col].u, skyboxTopTexcoords[row+1][col].v);
        glVertex3f(skyboxTopVertices[row+1][col].x,    skyboxTopVertices[row+1][col].y,   skyboxTopVertices[row+1][col].z);
        }
    }
    glEnd();
    glPopMatrix();

    // BOTTOM WALL ZNEG
    glBindTexture(GL_TEXTURE_2D, skyboxBottom);
    glPushMatrix();
    glTranslatef(camera->pos.x, camera->pos.y - 1, camera->pos.z);
    glRotatef(270, 1.0, 0.0, 0.0);
    glRotatef(180, 0, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    for (int row=0; row<SKYBOX_SEGMENTS; row++) {
        for (int col=0; col<SKYBOX_SEGMENTS; col++) {
        glTexCoord2f(skyboxBottomTexcoords[row][col].u, skyboxBottomTexcoords[row][col].v);
        glVertex3f(skyboxBottomVertices[row][col].x,    skyboxBottomVertices[row][col].y,     skyboxBottomVertices[row][col].z);

        glTexCoord2f(skyboxBottomTexcoords[row][col+1].u, skyboxBottomTexcoords[row][col+1].v);
        glVertex3f(skyboxBottomVertices[row][col+1].x,    skyboxBottomVertices[row][col+1].y,   skyboxBottomVertices[row][col+1].z);

        glTexCoord2f(skyboxBottomTexcoords[row+1][col+1].u, skyboxBottomTexcoords[row+1][col+1].v);
        glVertex3f(skyboxBottomVertices[row+1][col+1].x,    skyboxBottomVertices[row+1][col+1].y, skyboxBottomVertices[row+1][col+1].z);

        glTexCoord2f(skyboxBottomTexcoords[row+1][col].u, skyboxBottomTexcoords[row+1][col].v);
        glVertex3f(skyboxBottomVertices[row+1][col].x,    skyboxBottomVertices[row+1][col].y,   skyboxBottomVertices[row+1][col].z);
        }
    }
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void drawAxes() {
    glDisable(GL_LIGHTING);
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
    glEnable(GL_LIGHTING);
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
    glDisable(GL_LIGHTING);
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
    glEnable(GL_LIGHTING);
}

void shipWarning(ship *ship) {
    glDisable(GL_LIGHTING);
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
    glEnable(GL_LIGHTING);
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