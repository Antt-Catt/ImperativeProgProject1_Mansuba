#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include "game.h"

unsigned int achiev4;
unsigned int nb_turns;
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
  return UINT_MAX;
}

/** Chooses random move for piece in position p */
unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p)
{
  unsigned int tmp;
  unsigned int count = 0;

  while (p == UINT_MAX)
  {
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
    if (tmp != UINT_MAX || count > HEIGHT)
    {
      return UINT_MAX;
    }
    count++;
  }
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

/** Shows world w*/
void print_world(struct world_t *w)
{
  if (nb_turns<10)
  {
  printf("▒░▒▒░░▒▒▒░  TURN N 0%d  ░▒▒▒░░▒▒░▒\n", nb_turns);
  printf("▒░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░▒\n\n");
  }
  else{
  printf("▒░▒▒░░▒▒▒░  TURN N %d  ░▒▒▒░░▒▒░▒\n", nb_turns);
  printf("▒░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░▒\n\n");
  }
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
        printf("·\t");
      }
      else if (world_get(w, i * WIDTH + j) == BLACK)
      {
        switch (world_get_sort(w, j + i * WIDTH))
        {
        case 1:
          printf("♟\t");
          break;
        case 2:
          printf("♜\t");
          break;
        case 3:
          printf("♝\t");
          break;
        default:
          break;
        }
      }
      else if (world_get(w, i * WIDTH + j) == WHITE)
      {
        switch (world_get_sort(w, j + i * WIDTH))
        {
        case 1:
          printf("♙\t");
          break;
        case 2:
          printf("♖\t");
          break;
        case 3:
          printf("♗\t");
          break;
        default:
          break;
        }
      }
      else
      {
        printf("X\t\t");
      }
    }
    printf("\n\n");
  }
  printf("▒░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░▒\n");
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
