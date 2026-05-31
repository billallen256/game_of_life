#include <stdint.h>
#include <stdio.h>

#include "gol64.h"

void print_state(uint64_t* state) {
    int row = 0;
    int bit = 0;

    for (row = 0; row < GOL_SIZE; ++row) {
        printf("%02d ", row);

        for (bit = 0; bit < GOL_SIZE; ++bit) {
            uint64_t v = 0x8000000000000000 >> bit;
            if ((state[row] & v) == v) printf("X");
            else printf(".");
        }
        printf("\n");
    }
}

int main(void) {
    uint64_t frames[2][GOL_SIZE];
    uint64_t generation = 0;
    size_t curr_frame = 0;
    size_t next_frame = 1;

    set_zero_state(frames[0]);
    set_zero_state(frames[1]);
    create_glider(frames[0], 5, 5);

    for (generation = 0; generation < 1000000; ++generation) {
        next_frame = (curr_frame + 1) % 2;
        set_next_state(frames[curr_frame], frames[next_frame]);
        curr_frame = next_frame;
    }

    print_state(frames[curr_frame]);
    printf("Population %d\n", get_population(frames[curr_frame]));

    return 0;
}
