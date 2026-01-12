#ifndef _LOGGER_H
#define _LOGGER_H

#include <stdio.h>
#include "pso.h"

void init_logger(const char *filename);

void log_save(int iteration, const Particle *Particles, int num_particles);

void close_logger();

#endif