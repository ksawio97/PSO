#ifndef _MAP_H
#define _MAP_H

#include "utils.h"

typedef struct {
    Size size;
    double *signals;
} Map;

void read_map(const char *filename);

Size get_map_size();

void clear_map();

double get_map_signal(const Position pos);

#endif
