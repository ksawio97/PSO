#include "../include/logger.h"
#include <stdio.h>

static FILE *log_file;

void init_logger(const char *filename){
    log_file = fopen(filename, "w");
    fprintf(log_file, "iter,i,x,y,sig\n");
}

void log_save(int iteration, const Particle *Particles, int num_particles){
    for(int i = 0; i < num_particles; i++){
        fprintf(log_file, "%d,%d,%f,%f,%f\n", iteration, i, Particles[i].pos.x, Particles[i].pos.y, Particles[i].sig);
    }
}

void close_logger() {
    if (log_file == NULL) {
        return;
    }
    fclose(log_file);
}
