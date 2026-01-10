#ifndef _MAP_H
#define _MAP_H

typedef struct {
    int w, h;
    double *signals;
} Map;

void read_map(const char *filename);

void clear_map();

double get_val(const int r, const int c);

#endif
