#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/map.h"
#include "../include/pso.h"
#include "../include/logger.h"

int main(int argc, char** argv) {
    srand(time(NULL));
    
    if(argc < 2){
        printf("Error: you need to provide map file path\n");
        return 1;
    }

    int save_interval = 0;

    char* map_file = argv[1];
    int particle_count = 30, iter_count = 100;
    Config config = {0.5, 1.0, 1.0};

    for(int i = 2; i < argc; i++){
        if(strcmp(argv[i], "-p") == 0 && i + 1 < argc){
            particle_count = atoi(argv[i + 1]);
            if (particle_count <= 0) {
                printf("Error: There must be atleast 1 particle\n");
                return 1;
            }
        }
        else if(strcmp(argv[i], "-i") == 0 && i + 1 < argc){
            iter_count = atoi(argv[i + 1]);
            if (iter_count <= 0) {
                printf("Error: There must be atleast 1 iteration\n");
                return 1;
            }
        }
        else if(strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            if (!read_config(argv[i + 1], &config)) {
                printf("Error: Couldn't read %s config file\n", argv[i + 1]);
                return 1;
            }
        }
        else if(strcmp(argv[i], "-n") == 0 && i + 1 < argc){
            save_interval = atoi(argv[i + 1]);
            if (save_interval <= 0) {
                printf("Error: You can't save to log every <0 steps\n");
                return 1;
            }
        } else if (i + 1 == argc && argv[i][0] == '-') {
            printf("Error: You need to provide an argument to %s flag\n", argv[i]);
            return 1;
        }
        
        i++;
    }

    if (save_interval) {       
        init_logger("res/log.csv");
    }

    read_map(map_file);
    init_swarm(particle_count, config, get_map_size());
    
    if(save_interval > 0){
        log_save(0, get_swarm_particles(), particle_count);  
    }

    for(int i = 0; i < iter_count; i++){
        iter_swarm();
        
        int current_step = i + 1;
        if(save_interval > 0 && current_step % save_interval == 0){
            log_save(current_step, get_swarm_particles(), particle_count);  
        }
    }
    
    clear_swarm();
    clear_map();
    close_logger();
    
    return 0;
}
