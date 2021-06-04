#include "asteroid.h"

vec3d asteroidVertices[ASTEROID_DIVISIONS + 1][ASTEROID_DIVISIONS + 1];
int angle = 0;

void initAsteroidVertices() {
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

    // Set the random rotation direction.
    asteroid->rotate.x = rand() % (1 + 1 - 0) + 0;
    asteroid->rotate.y = rand() % (1 + 1 - 0) + 0;
    asteroid->rotate.z = rand() % (1 + 1 - 0) + 0;
}

void drawAsteroid(asteroid *asteroid) {
    // Brass
    float matAmbient[] ={ 0.329412f, 0.223529f, 0.027451f,1.0f };
    float matDiffuse[] ={ 0.780392f, 0.568627f, 0.113725f, 1.0f };
    float matSpecular[] ={ 0.992157f, 0.941176f, 0.807843f, 1.0f };
    float matShine[] = { 27.8974f };

    // setup materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    
    // Drawing the asteroid.
    glPushMatrix();
    glTranslatef(asteroid->pos.x, asteroid->pos.y, asteroid->pos.z);
    // Increase the angle at which the asteroid rotates.
    angle++;
    // Rotate the asteroid at a random angle.
    glRotatef(angle, asteroid->rotate.x, asteroid->rotate.y, asteroid->rotate.z);
    glScalef(asteroid->size, asteroid->size, asteroid->size);

    int i, j;
    vec3d *v1, *v2;
    for (j = 0; j < ASTEROID_DIVISIONS; j++) { 
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
        // Check for collisions on the X-Axis walls.
        if(asteroid->pos.x + asteroid->size >= ARENA_RADIUS || asteroid->pos.x - asteroid->size <= -ARENA_RADIUS) {
            // Invert the asteroid's directional vector on the X-Axis.
            asteroid->dir.x = -asteroid->dir.x;
        }
        // Check for collisions on the Y-Axis walls.
        if(asteroid->pos.y + asteroid->size >= ARENA_RADIUS || asteroid->pos.y - asteroid->size <= -ARENA_RADIUS) {
            // Invert the asteroid's directional vector on the Y-Axis.
            asteroid->dir.y = -asteroid->dir.y;
        }
        // Check for collisions on the Z-Axis walls.
        if(asteroid->pos.z + asteroid->size >= ARENA_RADIUS || asteroid->pos.z - asteroid->size <= -ARENA_RADIUS) {
            // Invert the asteroid's directional vector on the Z-Axis.
            asteroid->dir.z = -asteroid->dir.z;
        } 
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

void asteroidBouncing(asteroid *a, asteroid *a2) {
    if((a->alive && a2->alive) && (a->activated && a2->activated)) {
        vec3d result = distanceBetweenPoints(a->pos, a2->pos);
        float length = PYTHAGORAS(result.x, result.y, result.z);

        // If the ship and asteroid are touching, or inside one another.
        if(length < a->size + a2->size) {
            a->dir.x = -a->dir.x;
            a->dir.y = -a->dir.y;
            a->dir.z = -a->dir.z;

            a2->dir.x = -a->dir.x;
            a2->dir.y = -a->dir.y;
            a2->dir.z = -a->dir.z;
            printf("aaa\n");
        }
    }
}