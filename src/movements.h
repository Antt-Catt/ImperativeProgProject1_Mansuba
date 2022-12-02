#ifndef __MOVEMENTS_H__
#define __MOVEMENTS_H__

/** Sub function for possible_mvts */ 
void possible_mvts_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init);

/** Returns all possible movements for piece at index idx i */
set_t possible_mvts(unsigned int idx, struct world_t *w);

/** Move piece in position p to position m */
void move_piece(struct world_t *w, unsigned int p, unsigned int m);

#endif // __MOVEMENTS_H__