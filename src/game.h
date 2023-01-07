#ifndef __GAME_H__
#define __GAME_H__

#include "movements.h"

extern unsigned int current_player;

/** Initializes the game */
void init_game(struct world_t *w, unsigned int seed);

/** Initializes the positions of player p's pieces */
void init_player_set(struct world_t * w);

/** Chooses random piece belonging to current player */
unsigned int choose_random_piece_belonging_to(int current_player);

/** Chooses random move for piece in position p */
unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p);

/** Shows world w*/
void print_world(struct world_t *w);

/** Ends the game */
void end_game();

#endif // __GAME_H__
