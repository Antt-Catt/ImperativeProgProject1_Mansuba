#ifndef __PROJECT_H__
#define __PROJECT_H__

void possible_mvts_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init);

set_t possible_mvts(unsigned int idx, struct world_t *w);

void init_player_set(unsigned int p, struct world_t * w);

int check_simple_victory(unsigned int idx, unsigned int p);

int check_complex_victory(unsigned int p);

unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p);

void move_piece(struct world_t *w, unsigned int p, unsigned int m);

#endif // __PROJECT_H__
