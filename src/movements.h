#ifndef __MOVEMENTS_H__
#define __MOVEMENTS_H__

void possible_mvts_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init);

set_t possible_mvts(unsigned int idx, struct world_t *w);

void move_piece(struct world_t *w, unsigned int p, unsigned int m);

#endif // __MOVEMENTS_H__