#ifndef __PROJECT_H__
#define __PROJECT_H__

/** Sub function for possible_mvts */ 
void possible_mvts_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init);

/** Returns all possible movements for piece at index idx i */
set_t possible_mvts(unsigned int idx, struct world_t *w);

/** Initializes the positions of player p's pieces */
void init_player_set(unsigned int p, struct world_t * w);

/** Checks simple victory for piece at index idx of player p */
int check_simple_victory(unsigned int idx, unsigned int p);

/** Checks complex victory for player p */
int check_complex_victory(unsigned int p);

/** Chooses random piece belonging to current player */
unsigned int choose_random_piece_belonging_to(int current_player)

/** Chooses random move for piece in position p */
unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p);

/** Move piece in position p to position m */
void move_piece(struct world_t *w, unsigned int p, unsigned int m);

#endif // __PROJECT_H__
