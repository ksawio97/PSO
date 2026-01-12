#ifndef _PSO_H
#define _PSO_H

#include "utils.h"

typedef struct Particle {
    Position pos, velocity, best_pos;
    double sig, best_sig;
} Particle;

typedef struct Swarm {
    Position all_best_pos;
    double all_best_sig;

    Particle *particles;
    int particle_count;
    
    Config config;
} Swarm;

void init_swarm(const int particle_count, const Config config, const Size map_size);

void iter_swarm();

void clear_swarm();

Particle *get_swarm_particles();

#endif 
