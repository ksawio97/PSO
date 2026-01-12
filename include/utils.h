#ifndef _UTILS_H
#define _UTILS_H

typedef struct Size {
    int w, h;
} Size;

typedef struct Position {
    double x, y;
} Position;

typedef struct Config {
    double w;
    double c1, c2;
} Config;

void read_config(char* filename, Config* config);

double random_num(double min, double max);

void read_nums(const int num_count, double nums[num_count], char *line);

#endif
