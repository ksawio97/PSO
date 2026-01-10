#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/map.h"
#include "../include/pso.h"

int main(int argc, char** argv) {
    srand(time(NULL));
    
    // TODO handle reading args from argv
    char* map_file = "res/test_map.txt";
    int particle_count = 30, iter_count = 100;
    Config config;
    config.w = 0.5;
    config.c1 = 1;
    config.c2 = 1;
    
    read_map(map_file);
    init_swarm(particle_count, config, get_map_size());
    
    for (int i = 0; i < iter_count; i++) {
        iter_swarm();
    }
    
    // get positions
    Position partilces[particle_count];
    get_particles_positions(partilces);

    for (int i = 0; i < particle_count; i++) {
        printf("Particle %d pos: %.2f %.2f\n", i + 1, partilces[i].x, partilces[i].y);
    }
    
    clear_swarm();
    clear_map();
    return 0;
}
