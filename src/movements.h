#ifndef __MOVEMENTS_H__
#define __MOVEMENTS_H__

#include "neighbors.h"
#include "world.h"
#include "set.h"
#include "achiev1.h"
#include "achiev3.h"

extern set_t black_init_set;
extern set_t black_current_set;
extern set_t white_init_set;
extern set_t white_current_set;

set_t possible_drts();

/** Sub function for possible_mvts */ 
void possible_mvts_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init);

/** Returns all possible movements for piece at index idx i */
set_t possible_mvts(unsigned int idx, struct world_t *w);

/** Move piece in position p to position m */
unsigned int move_piece(struct world_t *w, unsigned int p, unsigned int m);

set_t achiev4_function(set_t *set, unsigned int player);

#endif // __MOVEMENTS_H__
