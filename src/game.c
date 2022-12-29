#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include "game.h"

//0 to not apply achiev4 rules, otherwise apply
unsigned int achiev4;

/** Initializes the positions of player p's pieces */
void init_player_set(unsigned int p, struct world_t *w)
{
  for (int i = 0; i < HEIGHT; i++)
  {
    if (p == BLACK)
    {
      world_set(w, WIDTH * i, p);
      world_set_sort(w, WIDTH * i, PAWN);
      black_init_set.ptr[i] = WIDTH * i;
      black_current_set.ptr[i] = WIDTH * i;
    }
    else
    {
      world_set(w, WIDTH * i + WIDTH - 1, p);
      world_set_sort(w, WIDTH * i + WIDTH - 1, PAWN);
      white_init_set.ptr[i] = WIDTH * i + WIDTH - 1;
      white_current_set.ptr[i] = WIDTH * i + WIDTH - 1;
    }
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
    unsigned int tmp = black_current_set.size - 1;
    int i = (rand() % (tmp - 0 + 1)) + 0;
    return black_current_set.ptr[i];
  }
  unsigned int tmp = white_current_set.size - 1;
  int i = (rand() % (tmp - 0 + 1)) + 0;
  return white_current_set.ptr[i];
}

/** Chooses random move for piece in position p */
unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p)
{
  set_t set = possible_mvts(p, w);
  print_set(&set);
  unsigned int player = world_get(w, p);
  if (achiev4 != 0)
  {
    // changes set if we want achiev4 conditions to take place
    set = achiev4_function(&set, player);
  }
  print_set(&set);
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
    if (get_neighbors_seed() == 1 && i%2 == 1)
    {
      printf("\t");
    }
    for (int j = 0; j < WIDTH; j++)
    {
      if (world_get_sort(w, i * WIDTH + j) == NO_SORT)
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
        printf("X");
      }
    }
    printf("\n\n");
  }
  printf("\n====================================\n\n");
}
