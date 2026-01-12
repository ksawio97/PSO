#include <stdlib.h>
#include <stdbool.h>

#include "../include/pso.h"
#include "../include/utils.h"
#include "../include/map.h"

static Swarm *swarm;

void init_swarm(const int particle_count, const Config config, const Size map_size) {
    extern Swarm *swarm;
    
    swarm = malloc(sizeof(Swarm));
    swarm->particles = malloc(sizeof(Particle) * particle_count);
    swarm->particle_count = particle_count;
    
    for (int i = 0; i < particle_count; i++) {
        Particle *curr = &swarm->particles[i];
        // init position and velocity
        curr->pos.x = curr->best_pos.x = random_num(0, map_size.w);
        curr->pos.y = curr->best_pos.y = random_num(0, map_size.h);
        curr->velocity.x = 0;
        curr->velocity.y = 0;
        // get curr signal
        curr->sig = curr->best_sig = get_map_signal(curr->pos);
        // update best signal
        if (curr->best_sig > swarm->all_best_sig) {
            swarm->all_best_sig = curr->best_sig;
            swarm->all_best_pos.x = curr->best_pos.x;
            swarm->all_best_pos.y = curr->best_pos.y;
        }
    }

    swarm->config.w = config.w;
    swarm->config.c1 = config.c1;
    swarm->config.c2 = config.c2;
}


void iter_particle(Particle *particle) {
    // get current velocity
    particle->velocity.x = swarm->config.w * particle->velocity.x + swarm->config.c1 * random_num(0, 1) * (particle->best_pos.x - particle->pos.x) + swarm->config.c2 * random_num(0, 1) * (swarm->all_best_pos.x - particle->pos.x);
    particle->velocity.y = swarm->config.w * particle->velocity.y + swarm->config.c1 * random_num(0, 1) * (particle->best_pos.y - particle->pos.y) + swarm->config.c2 * random_num(0, 1) * (swarm->all_best_pos.y - particle->pos.y);
    
    // new position
    particle->pos.x = particle->pos.x + particle->velocity.x;
    particle->pos.y = particle->pos.y + particle->velocity.y;

    // get current signal
    particle->sig = get_map_signal(particle->pos);

    // update best signal
    if (particle->sig > particle->best_sig) {
        particle->best_pos.x = particle->pos.x;
        particle->best_pos.y = particle->pos.y;

        particle->best_sig = particle->sig;
    }
}

void iter_swarm() { 
    for (int i = 0; i < swarm->particle_count; i++) {
        Particle *curr = &swarm->particles[i];
        iter_particle(curr);

        // update all particles best signal
        if (curr->best_sig > swarm->all_best_sig) {
            swarm->all_best_sig = curr->best_sig;

            swarm->all_best_pos.x = curr->best_pos.x;
            swarm->all_best_pos.y = curr->best_pos.y;
        }
    }
}

void clear_swarm() {
    free(swarm->particles);
    free(swarm);
    swarm = NULL;
}

Particle* get_swarm_particles() {
    if (swarm == NULL) return NULL;
    return swarm->particles;
}
