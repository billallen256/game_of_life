#include "gol64.h"

void set_zero_state(uint64_t* state) {
    size_t i = 0;

    for (i = 0; i < GOL_SIZE; ++i) {
        state[i] = 0;
    }
}

void set_rand_state(uint64_t* state) {
    size_t i = 0;

    for (i = 0; i < GOL_SIZE; ++i) {
        state[i] = 0xffffffff;  /* TODO random from env */
    }
}

void create_glider(uint64_t* state, int x, int y) {
    set_occupied(state, true, x, y);
    set_occupied(state, true, x+2, y);
    set_occupied(state, true, x+1, y+1);
    set_occupied(state, true, x+2, y+1);
    set_occupied(state, true, x+1, y+2);
}

int wrap(int val) {
    if (val < 0) return GOL_SIZE - 1;
    if (val > GOL_SIZE-1) return 0;
    return val;
}

bool get_occupied(uint64_t* state, int x, int y) {
    size_t row = wrap(y);
    int shift = wrap(x);
    uint64_t col = 0;
    col = 0x8000000000000000 >> shift;
    return (state[row] & col) == col;
}

uint64_t rotate_right(uint64_t x, int n) {
    return (x >> n) | (x << (GOL_SIZE - n));
}

int neighbor_count2(uint64_t* state, int x, int y) {
    uint64_t row_above = state[wrap(y-1)];
    uint64_t row_at = state[y];
    uint64_t row_below = state[wrap(y+1)];
    int rot = wrap(x-1);
    uint64_t mask_above_below = rotate_right(0xe000000000000000, rot);
    uint64_t mask_at = rotate_right(0xa000000000000000, rot);
    return count_ones(row_above&mask_above_below) + count_ones(row_at&mask_at) + count_ones(row_below&mask_above_below);
}

int neighbor_count(uint64_t* state, int x, int y) {
    int neighbors = 0;
    if (get_occupied(state, x-1, y-1)) ++neighbors;
    if (get_occupied(state, x-1, y)) ++neighbors;
    if (get_occupied(state, x-1, y+1)) ++neighbors;
    if (get_occupied(state, x, y-1)) ++neighbors;
    if (get_occupied(state, x, y+1)) ++neighbors;
    if (get_occupied(state, x+1, y-1)) ++neighbors;
    if (get_occupied(state, x+1, y)) ++neighbors;
    if (get_occupied(state, x+1, y+1)) ++neighbors;
    return neighbors;
}

bool get_life(uint64_t* state, int x, int y) {
    bool alive = false;
    /* int neighbors = neighbor_count(state, x, y); */
    int neighbors = 0;
    if (get_occupied(state, x-1, y-1)) ++neighbors;
    if (get_occupied(state, x-1, y)) ++neighbors;
    if (get_occupied(state, x-1, y+1)) ++neighbors;
    if (get_occupied(state, x, y-1)) ++neighbors;
    if (get_occupied(state, x, y+1)) ++neighbors;
    if (get_occupied(state, x+1, y-1)) ++neighbors;
    if (get_occupied(state, x+1, y)) ++neighbors;
    if (get_occupied(state, x+1, y+1)) ++neighbors;

    alive = get_occupied(state, x, y);

    if (alive && neighbors < 2) return false;  /* underpopulation */
    if (alive && neighbors == 2) return true;  /* continue if alive */
    if (neighbors == 3) return true;           /* always continue (reproduction) */
    if (alive && neighbors > 3) return false;  /* overpopulation */
    return false;                              /* dead stays dead */
}

void set_occupied(uint64_t* state, bool occupied, int x, int y) {
    if (occupied) {
        state[y] = state[y] | (0x8000000000000000 >> x);
    } else {
        state[y] = state[y] & ~(0x8000000000000000 >> x);
    }
}

void set_next_state(uint64_t* curr_state, uint64_t* next_state) {
    int x = 0;
    int y = 0;

    set_zero_state(next_state);

    for (y = 0; y < GOL_SIZE; ++y) {
        for (x = 0; x < GOL_SIZE; ++x) {
            set_occupied(next_state, get_life(curr_state, x, y), x, y);
        }
    }
}

int count_ones(uint64_t x) {
    x = (x & (0x5555555555555555)) + ((x >> 1) & (0x5555555555555555));
    x = (x & (0x3333333333333333)) + ((x >> 2) & (0x3333333333333333));
    x = (x & (0x0f0f0f0f0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f0f0f0f0f));
    x = (x & (0x00ff00ff00ff00ff)) + ((x >> 8) & (0x00ff00ff00ff00ff));
    x = (x & (0x0000ffff0000ffff)) + ((x >> 16) & (0x0000ffff0000ffff));
    x = (x & (0x00000000ffffffff)) + ((x >> 32) & (0x00000000ffffffff));
    return (int) x;
}

int get_population2(uint64_t* state) {
    int population = 0;
    int row = 0;

    for (row = 0; row < GOL_SIZE; ++row) {
        population += count_ones(state[row]);
    }

    return population;
}

int get_population(uint64_t* state) {
    int population = 0;
    int row = 0;
    uint64_t x = 0;

    for (row = 0; row < GOL_SIZE; ++row) {
        x = state[row];
        x = (x & (0x5555555555555555)) + ((x >> 1) & (0x5555555555555555));
        x = (x & (0x3333333333333333)) + ((x >> 2) & (0x3333333333333333));
        x = (x & (0x0f0f0f0f0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f0f0f0f0f));
        x = (x & (0x00ff00ff00ff00ff)) + ((x >> 8) & (0x00ff00ff00ff00ff));
        x = (x & (0x0000ffff0000ffff)) + ((x >> 16) & (0x0000ffff0000ffff));
        x = (x & (0x00000000ffffffff)) + ((x >> 32) & (0x00000000ffffffff));
        population += x;
    }

    return population;
}
