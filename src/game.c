#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include "game.h"

//0 to not apply achiev4 rules, otherwise apply
unsigned int achiev4;

/** Initializes the parameters of the game depends on what achievs are selected */
void init_game(struct world_t *w, unsigned int seed, unsigned int prison)
{
  init_neighbors(seed);
  
  black_init_set = init_set(HEIGHT);
  white_init_set = init_set(HEIGHT);
  black_current_set = init_set(HEIGHT);
  white_current_set = init_set(HEIGHT);

  if (prison != 0)
  {
    black_prison = init_set(0);
    white_prison = init_set(0);
  }

  init_player_set(w);
}

/** Initializes the positions of player p's pieces */
void init_player_set(struct world_t *w)
{
  for (int i = 0; i < HEIGHT; i++)
  {
    if (i == 0 || i == 3)
    {
      world_set(w, WIDTH * i, BLACK);
      world_set_sort(w, WIDTH * i, PAWN);
      world_set(w, WIDTH * i + WIDTH - 1, WHITE);
      world_set_sort(w, WIDTH * i + WIDTH - 1, PAWN);
    }
    else if (i == 1)
    {
      world_set(w, WIDTH * i, BLACK);
      world_set_sort(w, WIDTH * i, TOWER);
      world_set(w, WIDTH * i + WIDTH - 1, WHITE);
      world_set_sort(w, WIDTH * i + WIDTH - 1, TOWER);
    }
    else
    {
      world_set(w, WIDTH * i, BLACK);
      world_set_sort(w, WIDTH * i, ELEPHANT);
      world_set(w, WIDTH * i + WIDTH - 1, WHITE);
      world_set_sort(w, WIDTH * i + WIDTH - 1, ELEPHANT);
    }
    black_init_set.ptr[i] = WIDTH * i;
    black_current_set.ptr[i] = WIDTH * i;
    white_init_set.ptr[i] = WIDTH * i + WIDTH - 1;
    white_current_set.ptr[i] = WIDTH * i + WIDTH - 1;
  }
}

/** Checks simple victory for piece at index idx of player p */
int check_simple_victory(unsigned int idx, unsigned int p)
{
  if (p == BLACK)
  {
    if (exist_in_set(&white_init_set, idx) != UINT_MAX)
    {
      return p;
    }
  }
  else
  {
    if (exist_in_set(&black_init_set, idx) != UINT_MAX)
    {
      return p;
    }
  }
  return 0;
}

/** Checks complex victory for player p */
int check_complex_victory(unsigned int p)
{
  int j = 0;
  int i = 0;
  if (p == BLACK)
  {
    if (black_prison.size != 0)
    {
      return 0;
    }
    while (i < black_current_set.size)
    {
      if (check_simple_victory(black_current_set.ptr[i], BLACK) == 0)
      {
        j = 1;
      }
      else
      {
        delete_from_set(&black_current_set, black_current_set.ptr[i]);
        i--;
      }
      i++;
    }
  }
  else
  {
    if ((white_prison).size != 0)
    {
      return 0;
    }
    while (i < white_current_set.size)
    {
      if (check_simple_victory(white_current_set.ptr[i], WHITE) == 0)
      {
        j = 1;
      }
      else
      {
        delete_from_set(&white_current_set, white_current_set.ptr[i]);
        i--;
      }
      i++;
    }
  }
  if (j == 1)
  {
    return 0;
  }
  if (p == BLACK)
  {
    printf("Victoire complexe pour BLACK\n");
  }
  else
  {
    printf("Victoire complexe pour WHITE\n");
  }
  return 1;
}

/** Chooses random piece belonging to current player */
unsigned int choose_random_piece_belonging_to(int current_player)
{
  if (current_player == BLACK)
  {
    unsigned int tmp = black_current_set.size + black_prison.size - 1;
    int i = (rand() % (tmp - 0 + 1)) + 0;
    if (i < black_current_set.size)
    {
      return black_current_set.ptr[i];
    }
  }
  if (current_player == WHITE)
  {
    unsigned int tmp = white_current_set.size + white_prison.size - 1;
    int i = (rand() % (tmp - 0 + 1)) + 0;
    if (i < white_current_set.size)
    {
      return white_current_set.ptr[i];
    }
  }
  return UINT_MAX;
}

/** Chooses random move for piece in position p */
unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p)
{
  unsigned int tmp;
  unsigned int player = world_get(w, p);
  while (p == UINT_MAX)
  {
    tmp = escape(player, w);
    if (tmp == UINT_MAX)
    {
     p = choose_random_piece_belonging_to(player);
    }
    else
    {
      return UINT_MAX;
    }
  }
  set_t set = possible_mvts(p, w);
  if (achiev4 != 0)
  {
    // changes set if we want achiev4 conditions to take place
    set = achiev4_function(&set, player);
  }
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

/** Shows world w*/
void print_world(struct world_t *w)
{
  printf("\n");
  for (int i = 0; i < HEIGHT; i++)
  {
    if (get_neighbors_seed() == 1 && i % 2 == 1)
    {
      printf("\t");
    }
    for (int j = 0; j < WIDTH; j++)
    {
      if (world_get_sort(w, i * WIDTH + j) == NO_SORT && world_get(w, i * WIDTH + j) == NO_COLOR)
      {
        printf(".\t\t");
      }
      else if (world_get(w, i * WIDTH + j) == BLACK)
      {
        printf("B(%d)\t\t", world_get_sort(w, i * WIDTH + j));
      }
      else if (world_get(w, i * WIDTH + j) == WHITE)
      {
        printf("W(%d)\t\t", world_get_sort(w, j + i * WIDTH));
      }
      else
      {
        printf("X\t\t");
      }
    }
    printf("\n\n");
  }
  printf("\n====================================\n\n");
}
