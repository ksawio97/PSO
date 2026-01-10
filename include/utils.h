#ifndef _UTILS_H
#define _UTILS_H

typedef struct Size {
    int w, h;
} Size;

typedef struct Position {
    double x, y;
} Position;

double random_num(double min, double max);

void read_nums(const int num_count, double nums[num_count], char *line);

#endif
