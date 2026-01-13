#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/utils.h"

// rand num in range [min, max]
double random_num(double min, double max) {
    return ((double)rand() / (double)RAND_MAX) * (max - min) + min; 
}


void read_nums(const int num_count, double nums[num_count], char *line) {
    if (num_count == 0) {
        return;
    }

    // nums count
    int n = 0;
    
    double *number = &nums[0];
    *number = 0;

    int after_dot = 0;
    
    char *c = line;

    bool negative = false;
    if (*c == '-') {
        c++;
        negative = true;
    }

    for (; n < num_count && *c != '\0' && *c != EOF; c++) {
        // new num
        if (*c == ' ') {
            *number *= pow(-1.0, negative);
            number++;
            *number = 0;
            n++;
            after_dot = 0;
            negative = false;
            // new num is < 0
            if (*(c + 1) == '-') {
                c++;
                negative = true;
            }
            continue;
        }
        // decimals start
        if (*c == '.') {
            after_dot++;
            continue;
        }
        // decimals 
        if (after_dot) {
            *number += 1 / pow(10, after_dot++) * (*c - '0');
        } else {
            *number = 10 * (*number) + (*c - '0'); 
        }
    }
    *number *= pow(-1.0, negative);
}

bool read_config(char* filename, Config* config) {
    if (filename == NULL) {
        return false;
    }
    FILE* config_file = fopen(filename, "r");
    if (config_file != NULL) {
        fscanf(config_file, "%lf %lf %lf", &config->w, &config->c1, &config->c2);
        fclose(config_file);
        return true;
    }

    return false;
}
