#ifndef __PROJECT_H__
#define __PROJECT_H__

void mvt_possibles_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init);

set_t mvt_possibles(unsigned int idx, struct world_t *w);

void init_player_set(unsigned int p, struct world_t * w);

int check_simple_victory(unsigned int idx, unsigned int p);

int check_complex_victory(unsigned int p);

#endif // __PROJECT_H__
