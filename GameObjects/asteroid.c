#include "asteroid.h"

void initAsteroid(asteroid *asteroid) {
    // Set the vertices of the asteroid.
    const float r = 1.0;
    float theta, phi;
    vec3d vertex;
    float step_theta = 2.0 * M_PI / ASTEROID_DIVISIONS;
    float step_phi = M_PI / ASTEROID_DIVISIONS;
    phi = 0;
    for (int j = 0; j <= ASTEROID_DIVISIONS; j++, phi += step_phi) {
            theta = 0;
            for (int i = 0; i <= ASTEROID_DIVISIONS; i++, theta += step_theta) {
            vertex.x = r * sinf(phi) * cosf(theta);
            vertex.y = r * cosf(phi);
            vertex.z = r * sinf(phi) * sinf(theta);
            asteroid->vertices[i][j] = vertex;
        }
    }
}

void drawAsteroid(asteroid *asteroid) {
    float mat_diffuse[] = { 0.0, 0.8, 0.8, 1.0 };
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_shininess[] = { 100.0 };

    // setup materials
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // position and draw
    // glRotatef(g_platform_rotation, 0.0, 1.0, 0.0);
    glTranslatef(50.0, 50.0, 50.0);

    glPushMatrix();
    glScalef(10.0, 10.0, 10.0); // TODO: Replace 10.0 with asteroid->size, since we draw it as a 1x1, then scale to the random size.
    //glutSolidCube(1.0);
    int i, j;
    vec3d *v1, *v2;
    for (j = 0; j < ASTEROID_DIVISIONS; j++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (i=0; i<=ASTEROID_DIVISIONS; i++) {
        v1 = &asteroid->vertices[i][j];
        v2 = &asteroid->vertices[i][j+1];
        glNormal3f(v1->x, v1->y, v1->z);
        glVertex3f(v1->x, v1->y, v1->z);
        glNormal3f(v2->x, v2->y, v2->z);
        glVertex3f(v2->x, v2->y, v2->z);
        }
        glEnd();
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPopMatrix();
}