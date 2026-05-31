#ifndef _gol64_h_
#define _gol64_h_

#include <stddef.h>
#include <stdint.h>

#define GOL_SIZE 64

typedef enum { false, true } bool;

void set_zero_state(uint64_t* state);
void set_rand_state(uint64_t* state);
void create_glider(uint64_t* state, int x, int y);
void set_next_state(uint64_t* curr_state, uint64_t* next_state);
void set_occupied(uint64_t* state, bool occupied, int x, int y);
int neighbor_count(uint64_t* state, int x, int y);
int neighbor_count2(uint64_t* state, int x, int y);
int get_population(uint64_t* state);
int count_ones(uint64_t x);
int kernighan_count_ones(uint64_t x);
bool get_life(uint64_t* state, int x, int y);
bool get_occupied(uint64_t* state, int x, int y);

#endif
