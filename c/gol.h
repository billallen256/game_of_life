#ifndef _gol_h_
#define _gol_h_

#include <stddef.h>
#include <stdint.h>

#define GOL_SIZE 32

typedef enum { false, true } bool;

void set_zero_state(uint32_t* state);
void set_rand_state(uint32_t* state);
void create_glider(uint32_t* state, int x, int y);
void set_next_state(uint32_t* curr_state, uint32_t* next_state);
void set_occupied(uint32_t* state, bool occupied, int x, int y);
int neighbor_count(uint32_t* state, int x, int y);
int neighbor_count2(uint32_t* state, int x, int y);
int get_population(uint32_t* state);
int count_ones(uint32_t x);
bool get_life(uint32_t* state, int x, int y);
bool get_occupied(uint32_t* state, int x, int y);

#endif
