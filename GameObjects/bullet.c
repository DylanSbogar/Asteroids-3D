#include "bullet.h"

void initBullet(bullet *bullet, ship *ship) {
    // Set up the bullet.
    bullet->pos.x = ship->pos.x;
    bullet->pos.y = ship->pos.y;
    bullet->pos.z = ship->pos.z;

    bullet->dir.x = ship->dir.x;
    bullet->dir.y = ship->dir.y;
    bullet->dir.z = ship->dir.z;

    // Have the bullet's velocity be 50% faster than the ship's velocity.
    bullet->velocity = SHIP_VELOCITY * 1.5;

    bullet->size = BULLET_RADIUS;
    bullet->activated = false;

    bullet->r = 0;
    bullet->g = 1;
    bullet->b = 0;
}

void drawBullet(bullet *bullet) {
    // Draw a glutSolidSphere at the bullet's current position, and scale.
    //Brass
    float mat_ambient[] ={0.25f, 0.25f, 0.25f, 1.0f  };
    float mat_diffuse[] ={0.4f, 0.4f, 0.4f, 1.0f };
    float mat_specular[] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
    float shine[] = {76.8f};

    // setup materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    glPushMatrix();
        // glColor3f(bullet->r, bullet->g, bullet->b);
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
        // TODO: Remove this once textures are working?
        bullet->r = 0;
        bullet->g = 1;
        bullet->b = 0;
        
        if(bullet->pos.x + bullet->size >= ARENA_RADIUS || bullet->pos.x - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
        }
        if(bullet->pos.y + bullet->size >= ARENA_RADIUS || bullet->pos.y - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
        }
        if(bullet->pos.z + bullet->size >= ARENA_RADIUS || bullet->pos.z - bullet->size <= -ARENA_RADIUS) {
            bullet->activated = false;
        } 
    } else {
        // TODO: Remove this once textures are working?
        bullet->r = 1;
        bullet->g = 1;
        bullet->b = 1;
    }
}

void bulletAsteroidCollision(bullet *bullet, asteroid *asteroid) {
    // Get the distance between the bullet and the asteroid.
    vec3d result = distanceBetweenPoints(bullet->pos, asteroid->pos);
    float length = PYTHAGORAS(result.x, result.y, result.z);

    // Ensure the asteroid is activated, i.e. fully entered the arena in the case of larger asteroids.
    if(asteroid->activated) {
        if(length < asteroid->size + SHIP_LENGTH) {
            asteroid->alive = false;
            bullet->activated = false;
        }
    }
}