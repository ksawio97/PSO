#include <time.h>
#include <stdlib.h>

#include "../include/map.h"
#include "../include/utils.h"

int main(int argc, char** argv) {
    srand(time(NULL));
    
    // TODO handle reading args from argv
    char* map_file = "res/test_map.txt";
    int particle_count = 30, iter_count = 100;
    double w = 0.5, c_1 = 1, c_2 = 1, r_1 = random_num(0, 1), r_2 = random_num(0, 1);
    
    read_map(map_file);

    clear_map();
    return 0;
}
