#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"
#include "../include/map.h" 

#define LINE_BUF 2048

static Map *map;

void read_map(const char *filename) {
    extern Map *map;
    
    FILE *fh = fopen(filename, "r"); 
    if (fh == NULL) {
        // TODO add error assertion
        return;
    }
    map = malloc(sizeof(Map));
    // read width and height
    fscanf(fh, "%d %d\n", &(map->size.w), &(map->size.h));
    // allocate signals array
    map->signals = malloc(sizeof(double) * map->size.w * map->size.h);

    // read map line by line
    for (int r = 0; r < map->size.h; r++) {
        char *line = NULL;
        size_t line_size = 0;

        int line_len = getline(&line, &line_size, fh); 
        if (line_len > 0) {
            read_nums(map->size.w, &map->signals[r * map->size.w], line);
        }
        free(line);
    }

    fclose(fh);
}

bool in_map_bounds(const Position pos) {
    return pos.x >= 0 && pos.x <= map->size.w && pos.y >= 0 && pos.y <= map->size.h;
}

double get_map_signal(const Position pos) {
    if (!in_map_bounds(pos)) {
       return -DBL_MAX; 
    }
    const int r = (int)pos.y, c = (int)pos.x;
    return map->signals[r * map->size.w + c];
}

Size get_map_size() {
    return map->size;
}

void clear_map() {
    free(map->signals);
    free(map);
    map = NULL;
}
