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