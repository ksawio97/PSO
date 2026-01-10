#include "../include/map.h" 
#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

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
    fscanf(fh, "%d %d\n", &(map->w), &(map->h));
    // allocate signals array
    map->signals = malloc(sizeof(double) * map->w * map->h);

    // read map line by line
    for (int r = 0; r < map->h; r++) {
        char *line = NULL;
        size_t line_size = 0;

        int line_len = getline(&line, &line_size, fh); 
        if (line_len > 0) {
            read_nums(map->w, &map->signals[r * map->w], line);
        }
        free(line);
    }

    fclose(fh);
}

double get_val(const int r, const int c) {
    if (map == NULL || r < 0 || c < 0 || r >= map->h || c >= map->w) {
        // TODO asset error
        return 0;
    }
    return map->signals[r * map->w + c];
}

void clear_map() {
    free(map->signals);
    free(map);
    map = NULL;
}
