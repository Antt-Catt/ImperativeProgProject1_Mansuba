#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include "project.h"
#include "movements.h"
#include "neighbors.h"
#include "set.h"

set_t black_init_set;
extern set_t black_current_set;
set_t white_init_set;
extern set_t white_current_set;

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
      world_set(w, WIDTH * i + HEIGHT, p);
      world_set_sort(w, WIDTH * i + HEIGHT, PAWN);
      white_init_set.ptr[i] = WIDTH * i + HEIGHT;
      white_current_set.ptr[i] = WIDTH * i + HEIGHT;
    }
  }
}

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

unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p)
{
  set_t set = possible_mvts(p, w);
  if (set.size > 1)
  {
    unsigned int tmp = set.size - 1;
    int i = (rand() % (tmp - 0 + 1)) + 0;
    unsigned int x = set.ptr[i];
    delete_set(&set);
    return x;
  }
  return p;
}

void print_world(struct world_t *w)
{
  for (int i = 0; i < WORLD_SIZE; i++)
  {
    if (i % WIDTH == 0 && i != 0)
    {
      printf("\n");
    }
    printf("i=%d_s=%d_c=%d\t", i, world_get_sort(w, i), world_get(w, i));
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  int opt;
  int optc = 0;
  int MAX_TURNS;
  char victory_type[1];

  while ((opt = getopt(argc, argv, "s:m:t:")) != -1)
  {
    switch (opt)
    {
    case 's':
      optc++;
      srand(atoi(optarg));
      break;
    case 'm':
      MAX_TURNS = atoi(optarg);
      optc++;
      break;
    case 't':
      strcpy(victory_type, optarg);
      optc++;
      break;
    }
  }

  if (optc != 3)
  {
    printf("Options needed : -s -m -t\n");
    return 0;
  }

  int nb_turns = 0;
  struct world_t *w = world_init();
  init_neighbors(0);

  black_init_set = init_set(HEIGHT);
  white_init_set = init_set(HEIGHT);
  black_current_set = init_set(HEIGHT);
  white_current_set = init_set(HEIGHT);

  init_player_set(1, w);
  init_player_set(2, w);

  unsigned int current_player = (rand() % (2 - 1 + 1)) + 1;
  unsigned int p = choose_random_piece_belonging_to(current_player % 2 + 1);
  unsigned int m;

  if (strcmp(victory_type, "s") == 0)
  {
    while ((check_simple_victory(p, current_player % 2 + 1) == 0) && (nb_turns != MAX_TURNS))
    {
      p = choose_random_piece_belonging_to(current_player);
      m = choose_random_move_for_piece(w, p);
      move_piece(w, p, m);
      current_player = current_player % 2 + 1;
      nb_turns++;
      p = m;
    }
    if (current_player == BLACK)
    {
      printf("Victoire simple pour WHITE\n");
    }
    else
    {
      printf("Victoire simple pour BLACK\n");
    }
  }
  if (strcmp(victory_type, "c") == 0)
  {

    while ((check_complex_victory(current_player % 2 + 1) == 0) && (nb_turns != MAX_TURNS))
    {
      p = choose_random_piece_belonging_to(current_player);
      m = choose_random_move_for_piece(w, p);
      if (p != m)
      {
        move_piece(w, p, m);
      }
      current_player = current_player % 2 + 1;
      p = m;
      nb_turns++;
    }
  }

  delete_set(&black_current_set);
  delete_set(&white_current_set);
  delete_set(&black_init_set);
  delete_set(&white_init_set);

  return 0;
}
