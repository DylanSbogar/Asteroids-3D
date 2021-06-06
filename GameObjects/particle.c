#include "particle.h"

int particleIndex = 0;
particle particles[MAX_PARTICLES];

void particleController(float deltaTime) {
    for(int i = 0; i < MAX_PARTICLES; i++) {
        moveParticle(&particles[i], deltaTime);
        drawParticle(&particles[i]);
    }
}

void initParticle(particle *particle, vec3d pos, vec3d dir) {
    particle->pos.x = pos.x - 10 + (rand() % 20);
    particle->pos.y = pos.y - 10 + (rand() % 20);
    particle->pos.z = pos.z - 10 + (rand() % 20);

    particle->dir.x = rand() % (1 + 1 - -1) + -1;
    particle->dir.y = rand() % (1 + 1 - -1) + -1;
    particle->dir.z = rand() % (1 + 1 - -1) + -1;

    particle->velocity = 1;

    particle->radius = 5;
}

void launchParticle(particle *particle, vec3d pos, vec3d dir) {
    for(int i = 0; i < PARTICLE_AMT; i++) {
        initParticle(&particles[particleIndex++], pos, dir);
        if(particleIndex == MAX_PARTICLES -1) {
            particleIndex = 0;
        }
    }
}

void moveParticle(particle *particle, float deltaTime) {
    particle->pos.x += deltaTime * (particle->velocity * particle->dir.x);
    particle->pos.y += deltaTime * (particle->velocity * particle->dir.y);
    particle->pos.z += deltaTime * (particle->velocity * particle->dir.z);

    particle->radius *= 0.95;
}

void drawParticle(particle *particle) {
    glPushMatrix();
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

        glTranslatef(particle->pos.x, particle->pos.y, particle->pos.z);
        glScalef(particle->radius, particle->radius, particle->radius);
        glutSolidTetrahedron();
    glPopMatrix();
    // glEnable(GL_LIGHTING);
}