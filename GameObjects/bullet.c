#include "bullet.h"

void initBullet(bullet *bullet, ship *ship) {
    // Set up the bullet.
    bullet->pos.x = ship->pos.x;
    bullet->pos.y = ship->pos.y;
    bullet->pos.z = ship->pos.z;

    bullet->dir.x = ship->dir.x;
    bullet->dir.y = ship->dir.y;
    bullet->dir.z = ship->dir.z;

    // Have the bullet's velocity be 75% faster than the ship's velocity.
    bullet->velocity = SHIP_VELOCITY * 2;

    bullet->size = BULLET_RADIUS;
    bullet->activated = false;
}

void drawBullet(bullet *bullet) {
    //Brass
    float matAmbient[] ={ 0.25f, 0.25f, 0.25f, 1.0f };
    float matDiffuse[] ={0.4f, 0.4f, 0.4f, 1.0f };
    float matSpecular[] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
    float matShine[] = { 76.8f };

    // Setup materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    // Draw a glutSolidSphere at the bullet's current position, and scale.
    glPushMatrix();
        glTranslatef(bullet->pos.x, bullet->pos.y, bullet->pos.z);
        glScalef(bullet->size, bullet->size, bullet->size);
        glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void moveBullet(bullet *bullet, float deltaTime) {
    // Calculate the bullet's next position.
    bullet->pos.x += deltaTime * (bullet->velocity * bullet->dir.x);
    bullet->pos.y += deltaTime * (bullet->velocity * bullet->dir.y);
    bullet->pos.z += deltaTime * (bullet->velocity * bullet->dir.z);
}

void bulletCollision(bullet *bullet) {
    if(bullet->activated) {        
        if(bullet->pos.x + bullet->size >= ARENA_RADIUS || bullet->pos.x - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
        }
        if(bullet->pos.y + bullet->size >= ARENA_RADIUS || bullet->pos.y - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
        }
        if(bullet->pos.z + bullet->size >= ARENA_RADIUS || bullet->pos.z - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
        } 
    }
}

bool bulletAsteroidCollision(bullet *bullet, asteroid *asteroid) {
    // Get the distance between the bullet and the asteroid.
    vec3d result = distanceBetweenPoints(bullet->pos, asteroid->pos);
    float length = PYTHAGORAS(result.x, result.y, result.z);

    // Ensure the asteroid is activated, i.e. fully entered the arena in the case of larger asteroids.
    if(asteroid->activated && bullet->activated) {
        if(length < asteroid->size + SHIP_LENGTH) {
            asteroid->alive = false;
            bullet->activated = false;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}