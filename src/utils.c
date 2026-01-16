#include <stdio.h>
#include <string.h>
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

void read_config(char* filename, Config* config) {
    FILE* config_file = fopen(filename, "r");
    if (config_file != NULL) {
        fscanf(config_file, "%lf %lf %lf", &config->w, &config->c1, &config->c2);
        fclose(config_file);
    }
    fprintf(stderr, "Error: reading config file");
}

void read_params(char **argv, int argc, Config *config, int *save_interval, int *particle_count, int *iter_count) {

    char* filename = NULL;
    for(int i = 1; i < argc; i++) {

        if (argv[i][0] != '-' && filename == NULL) {
            filename = malloc(strlen(argv[i]));
            filename = argv[i];    
        }
        
        if (strlen(argv[i]) == 1 || i + 1 == argc) {
            continue;    
        }

        switch (argv[i][1]) {
            case 'p':
                *particle_count = atoi(argv[i + 1]);

                if (particle_count <= 0) {
                    fprintf(stderr, "Error: There must be atleast 1 particle\n");
                    exit(0);
                }
                break;
            case 'i':
                *iter_count = atoi(argv[i  + 1]);

                if (iter_count <= 0) {
                    fprintf(stderr, "Error: There must be atleast 1 iteration\n");
                    exit(0); 
                    return;
                }
                break;
            case 'c':
                read_config(argv[i + 1], config);
                
                break;
            case 'n':
                *save_interval = atoi(argv[i + 1]);
                if (save_interval <= 0) {
                    fprintf(stderr, "Error: You can't save to log every <0 steps\n");
                    exit(0);
                }
                break;
            i++;
        };

        if (filename != NULL) {
            fprintf(stderr, "Error: You need to provide filename map\n");
            exit(0);
        }
    }
}
