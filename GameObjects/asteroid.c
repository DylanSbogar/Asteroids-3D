#include "asteroid.h"

vec3d asteroidVertices[ASTEROID_DIVISIONS + 1][ASTEROID_DIVISIONS + 1];

void initAsteroidVertices(asteroid *asteroid) {

}

void initAsteroid(asteroid *asteroid, ship *ship) {
    // Set the position of the asteroid.
    float temp = (rand() % 360) / (double)360 * 2.0 * M_PI;
    asteroid->pos.x = (ASTEROID_SPAWN_RADIUS * cosf(temp)) * ARENA_RADIUS;
    asteroid->pos.y = (ASTEROID_SPAWN_RADIUS * sinf(temp)) * ARENA_RADIUS;
    asteroid->pos.z = (ASTEROID_SPAWN_RADIUS * sinf(temp)) * ARENA_RADIUS; 

    // Set the size of the asteroid.
    asteroid->size = rand() % (ASTEROID_MAX_SIZE + 1 - ASTEROID_MIN_SIZE) + ASTEROID_MIN_SIZE;

    // Set the velocity of the asteroid.
    asteroid->velocity = rand() % (ASTEROID_MAX_VELOCITY + 1 - ASTEROID_MIN_VELOCITY) + ASTEROID_MIN_VELOCITY;
    asteroid->velocity /= 1000;

    vec3d newVec = distanceBetweenPoints(asteroid->pos, ship->pos);
    float length = PYTHAGORAS(newVec.x, newVec.y, newVec.z);

    asteroid->dir.x = (newVec.x / length);
    asteroid->dir.y = (newVec.y / length);
    asteroid->dir.z = (newVec.z / length);

    // Set to false since asteroids start outside the arena.
    asteroid->activated = false;
    asteroid->alive = true;

    // DEBUG: Since asteroids start as inactive, colour them red by default.
    // TODO: Remove when textures are working??
    asteroid->r = 1;
    asteroid->g = 0;
    asteroid->b = 0;

    // Initialise the sphere's vertices. (Adapted from tutorial 10 code.)
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
        asteroidVertices[i][j] = vertex;
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
    
    // Drawing the asteroid.
    glPushMatrix();
    glTranslatef(asteroid->pos.x, asteroid->pos.y, asteroid->pos.z);
    glScalef(asteroid->size, asteroid->size, asteroid->size);

    int i, j;
    vec3d *v1, *v2;
    for (j = 0; j < ASTEROID_DIVISIONS; j++) {    // divide by 2 for hemisphere
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i <= ASTEROID_DIVISIONS; i++) {
            v1 = &asteroidVertices[i][j];
            v2 = &asteroidVertices[i][j+1];
            glNormal3f(v1->x, v1->y, v1->z);
            glVertex3f(v1->x, v1->y, v1->z);
            glNormal3f(v2->x, v2->y, v2->z);
            glVertex3f(v2->x, v2->y, v2->z);
        }
        glEnd();
    }
    glPopMatrix();

    // glPushMatrix();
    //     glColor3f(asteroid->r, asteroid->g, asteroid->b);
    //     glTranslatef(asteroid->pos.x, asteroid->pos.y, asteroid->pos.z);
    //     glScalef(asteroid->size, asteroid->size, asteroid->size);
    //     glutSolidSphere(1.0, ASTEROID_DIVISIONS, ASTEROID_DIVISIONS);
    // glPopMatrix();
}

void moveAsteroid(asteroid *asteroid, float deltaTime, int round) {
    // Calculate the asteroid's next position.
    asteroid->pos.x += deltaTime * (asteroid->velocity * asteroid->dir.x);
    asteroid->pos.y += deltaTime * (asteroid->velocity * asteroid->dir.y);
    asteroid->pos.z += deltaTime * (asteroid->velocity * asteroid->dir.z);
}

void asteroidWallCollision(asteroid *asteroid) {
    // The asteroid must be fully within the arena (activated) to be able to bounce off the wall.
    if(asteroid->activated) {
        // TODO: Remove when textures are working?
        asteroid->r = 1;
        asteroid->g = 1;
        asteroid->b = 1;
        // Check for collisions on the X-Axis walls.
        if(asteroid->pos.x + asteroid->size >= ARENA_RADIUS || asteroid->pos.x - asteroid->size <= -ARENA_RADIUS) {
            // Invert the asteroid's directional vector on the X-Axis.
            asteroid->dir.x = -asteroid->dir.x;
        }
        // Check for collisions on the Y-Axis walls.
        if(asteroid->pos.y + asteroid->size >= ARENA_RADIUS || asteroid->pos.y - asteroid->size <= -ARENA_RADIUS) {
            // Invert the asteroid's directional vector on the Y-Axis.
        }
        // Check for collisions on the Z-Axis walls.
        if(asteroid->pos.z + asteroid->size >= ARENA_RADIUS || asteroid->pos.z - asteroid->size <= -ARENA_RADIUS) {
            // Invert the asteroid's directional vector on the Z-Axis.
            asteroid->dir.z = -asteroid->dir.z;
        } 
    } else {
        // TODO: Remove when textures are working?
        asteroid->r = 1;
        asteroid->g = 0;
        asteroid->b = 0;
    }
}

void checkActivated(asteroid *asteroid) {
    // If the asteroid is fully inside the arena, activate it.
    if((asteroid->pos.x - asteroid->size > -ARENA_RADIUS && asteroid->pos.x + asteroid->size < ARENA_RADIUS) 
    && (asteroid->pos.y - asteroid->size > -ARENA_RADIUS && asteroid->pos.y + asteroid->size < ARENA_RADIUS) 
    && (asteroid->pos.z - asteroid->size > -ARENA_RADIUS && asteroid->pos.z + asteroid->size < ARENA_RADIUS)) {
        asteroid->activated = true;
    }
}

bool asteroidShipCollision(ship *ship, asteroid *asteroid) {
    vec3d result = distanceBetweenPoints(ship->pos, asteroid->pos);
    float length = PYTHAGORAS(result.x, result.y, result.z);

    // Only check collision if the asteroid has not been destroyed.
    if(asteroid->alive) {
        // If the ship and asteroid are touching, or inside one another.
        if(length < asteroid->size + SHIP_LENGTH) {
            // A true value will end the game.
            return true;
        } else {
            // A false value will not end the game.
            return false;
        }
    } else {
        return false;
    }
}