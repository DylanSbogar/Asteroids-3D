#include "ship.h"

void initShip(ship *ship) {
    ship->pos.x = 0;
    ship->pos.y = 0;
    ship->pos.z = 0;

    ship->dir.x = 0;
    ship->dir.y = 0;
    ship->dir.z = 0;

    // Set the ship velocity to be the same as the camera.
    ship->velocity = SHIP_VELOCITY;
}

void drawShip(const DrawObject* drawObject, ship *ship, float yaw, float roll, float pitch) {
    glPushMatrix();
    float matAmbient[] ={ 0.0f,0.0f,0.0f,1.0f };
    float matDiffuse[] ={ 0.5f,0.0f,0.0f,1.0f};
    float matSpecular[] ={0.7f,0.6f,0.6f,1.0f };
    float matShine[] = {32.0f} ;

    // setup materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    // glColor3f(1.0, 0.0, 1.0);
    glTranslatef(ship->pos.x, ship->pos.y, ship->pos.z);
    glRotatef(-yaw, 0, 1, 0);
    glRotatef(roll, 1, 0, 0);
    glRotatef(pitch, 0, 0, 1);
    glScalef(SHIP_LENGTH/3, SHIP_LENGTH/3, SHIP_LENGTH/3);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    if (drawObject->vb >= 1) {
        glBindBuffer(GL_ARRAY_BUFFER, drawObject->vb);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 36, (const void*)0);
        glNormalPointer(GL_FLOAT, 36, (const void*)(sizeof(float) * 3));
        glColorPointer(3, GL_FLOAT, 36, (const void*)(sizeof(float) * 6));

        glDrawArrays(GL_TRIANGLES, 0, 3 * drawObject->numTriangles);
    }
    glPopMatrix();

    // Draw the collision debug sphere.
    // glDisable(GL_LIGHTING);
    // glPushMatrix();
    //     glColor3f(0.0, 0.0, 0.3);
    //     glTranslatef(ship->pos.x, ship->pos.y, ship->pos.z);
    //     glScalef(SHIP_LENGTH, SHIP_LENGTH, SHIP_LENGTH);
    //     glutWireSphere(1.0, 16, 16);
    // glPopMatrix();
    // glEnable(GL_LIGHTING);
}

void moveShip(ship *ship, float deltaTime, int turnValue) {
    ship->pos.x += turnValue * (deltaTime * (ship->velocity * ship->dir.x));
    ship->pos.y += turnValue * (deltaTime * (ship->velocity * ship->dir.y));
    ship->pos.z += turnValue * (deltaTime * (ship->velocity * ship->dir.z));
}
