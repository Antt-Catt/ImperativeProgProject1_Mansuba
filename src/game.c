#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include "game.h"

unsigned int achiev4;
unsigned int current_player;

/** Initializes the parameters of the game depends on what achievs are selected */
void init_game(struct world_t *w, unsigned int seed)
{
  init_neighbors(seed);

  black_init_set = init_set(HEIGHT);
  white_init_set = init_set(HEIGHT);
  black_current_set = init_set(HEIGHT);
  white_current_set = init_set(HEIGHT);

  black_prison = init_set(0);
  white_prison = init_set(0);

  init_player_set(w);
}

/** Initializes the positions of player p's pieces */
void init_player_set(struct world_t *w)
{
  for (int i = 0; i < HEIGHT; i++)
  {
    world_set(w, WIDTH * i, BLACK);
    world_set(w, WIDTH * i + WIDTH - 1, WHITE);
    if ((i % 3) == 0)
    {
      world_set_sort(w, WIDTH * i, PAWN);
      world_set_sort(w, WIDTH * i + WIDTH - 1, PAWN);
    }
    else if ((i % 3 == 1))
    {
      world_set_sort(w, WIDTH * i, TOWER);
      world_set_sort(w, WIDTH * i + WIDTH - 1, ELEPHANT);
    }
    else
    {
      world_set_sort(w, WIDTH * i, ELEPHANT);
      world_set_sort(w, WIDTH * i + WIDTH - 1, TOWER);
    }
    black_init_set.ptr[i] = WIDTH * i;
    black_current_set.ptr[i] = WIDTH * i;
    white_init_set.ptr[i] = WIDTH * i + WIDTH - 1;
    white_current_set.ptr[i] = WIDTH * i + WIDTH - 1;
  }
}

/** Chooses random piece belonging to current player */
unsigned int choose_random_piece_belonging_to(int player)
{
  if (player == BLACK)
  {
    // tmp the total number of pieces owned by the player, this includes improsined pieces
    unsigned int tmp = black_current_set.size + (black_prison.size / 2) - 1;
    int i = (rand() % (tmp - 0 + 1)) + 0;
    if (i < black_current_set.size)
    {
      return black_current_set.ptr[i];
    }
  }
  if (player == WHITE)
  {
    unsigned int tmp = white_current_set.size + (white_prison.size / 2) - 1;
    int i = (rand() % (tmp - 0 + 1)) + 0;
    if (i < white_current_set.size)
    {
      return white_current_set.ptr[i];
    }
  }
  // if we choose a number higher than the size of the set of current pieces for a player, we choose to try to escape one of its imprisoned pieces
  // the UINT_MAX returned will be understood by the choose_random_move_for_piece function
  return UINT_MAX;
}

/** Chooses random move for piece in position p */
unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p)
{
  unsigned int tmp;
  unsigned int count = 0;

  while (p == UINT_MAX)
  {
    // we enter here if the choose_random_piece_belonging_to function chose to try to escape an improsined piece
    tmp = escape(current_player, w);
    if (tmp == UINT_MAX)
    {
      p = choose_random_piece_belonging_to(current_player);
      if (p != UINT_MAX)
      {
        unsigned int m = choose_random_move_for_piece(w, p);
        move_piece(w, p, m);
        return UINT_MAX;
      }
    }
    if (tmp != UINT_MAX || count > WORLD_SIZE)
    {
      // we enter here after trying multiple times to espace multiple pieces without succeeding
      return UINT_MAX;
    }
    count++;
  }

  // we have p != UINT_MAX
  set_t set = possible_mvts(p, w);
  if (set.size > 0)
  {
    unsigned int tmp = set.size - 1;
    int i = (rand() % (tmp - 0 + 1)) + 0;
    unsigned int x = set.ptr[i];
    delete_set(&set);
    return x;
  }
  delete_set(&set);
  return p;
}

void end_game()
{
  delete_set(&black_current_set);
  delete_set(&white_current_set);
  delete_set(&black_init_set);
  delete_set(&white_init_set);
  delete_set(&black_prison);
  delete_set(&white_prison);
}
