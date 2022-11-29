#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "world.h"
#include "neighbors.h"
#include "set.h"
//comment
set_t black_init_set;
set_t black_current_set;

set_t white_init_set;
set_t white_current_set;

extern struct world_t w;

void possible_mvts_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init)
{
  int j = 0;
  unsigned int idx_n;
  struct neighbors_t neigh_idx = get_neighbors(idx);
  if (exist_in_set(set, idx) == UINT_MAX && idx != init)
  {
    push_set(set, idx);
  }
  while (neigh_idx.n[j].i != UINT_MAX)
  {
    idx_n = neigh_idx.n[j].i;
    if (world_get_sort(w, idx_n) != 0)
    {
      idx_n = get_neighbor(idx_n, neigh_idx.n[j].d);
      if (world_get_sort(w, idx_n) == 0)
      {
        if (exist_in_set(set, idx_n) == UINT_MAX && idx_n != init)

        {
          possible_mvts_aux(set, idx_n, w, init);
        }
      }
    }
    j++;
  }
}

set_t possible_mvts(unsigned int idx, struct world_t *w)
{
  set_t set = init_set(0);
  struct neighbors_t neigh_idx = get_neighbors(idx);
  int j = 0;
  while (neigh_idx.n[j].i != UINT_MAX)
  {
    unsigned int idx_n = neigh_idx.n[j].i;
    if (world_get_sort(w, idx_n) == 0)
    {
      push_set(&set, idx_n);
    }
    else
    {
      idx_n = get_neighbor(idx_n, neigh_idx.n[j].d);
      if (world_get_sort(w, idx_n) == 0)
      {
        possible_mvts_aux(&set, idx_n, w, idx);
      }
    }
    j++;
  }
  return set;
}

void init_player_set(unsigned int p, struct world_t *w)
{
  for (int i = 0; i < HEIGHT; i++)
  {
    if (p == BLACK)
    {
      world_set(w, WIDTH * i, p);
      world_set_sort(w, WIDTH * i, PAWN);
      push_set(&black_init_set, WIDTH * i);
    }
    else
    {
      world_set(w, WIDTH * i + HEIGHT, p);
      world_set_sort(w, WIDTH * i, PAWN);
      push_set(&white_init_set, WIDTH * i + HEIGHT);
    }
  }
}

int check_simple_victory(unsigned int idx, unsigned int p)
{
  if (p == 1)
  {
    if (exist_in_set(&white_init_set, idx) != UINT_MAX)
    {
      printf("Victoire simple pour BLACK\n");
      return 1;
    }
  }
  else
  {
    if (exist_in_set(&black_init_set, idx) != UINT_MAX)
    {
      printf("Victoire simple pour WHITE\n");
      return 1;
    }
  }
  return 0;
}

int check_complex_victory(unsigned int p)
{
  if (p == 1)
  {
    for (int i = 0; i < HEIGHT; i++)
    {
      if (check_simple_victory(black_current_set.ptr[i], 1) == 0)
      {
        return 1;
      }
    }
  }
  else
  {
    for (int i = 0; i < HEIGHT; i++)
    {
      if (check_simple_victory(white_current_set.ptr[i], 2) == 0)
      {
        return 1;
      }
    }
  }
  return 0;
}

unsigned int choose_random_piece_belonging_to(int current_player)
{
  unsigned int tmp = HEIGHT - 1;
  int i = (rand() % (tmp - 0 + 1)) + 0;
  if (current_player == BLACK)
  {
    return black_current_set.ptr[i];
  }
  return white_current_set.ptr[i];
}

unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p)
{
  set_t set = possible_mvts(p, w);
  unsigned int tmp = set.size - 1;
  int i = (rand() % (tmp - 0 + 1)) + 0;
  return set.ptr[i];
}

void move_piece(struct world_t *w, unsigned int p, unsigned int m)
{
  unsigned int current_player = world_get(w, p);
  world_set(w, m, current_player);
  world_set_sort(w, m, PAWN);
  if (current_player == BLACK)
  {
    modif_set(&black_current_set, p, m);
  }
  else
  {
    modif_set(&white_current_set, p, m);
  }
  world_set(w, p, NO_COLOR);
  world_set_sort(w, p, NO_SORT);
}

int main(int argc, char *argv[])
{
  argc = argc;
  argv[0] = argv[0];
  /*choose_random_piece_belonging_to(w, current_player)
  world_init();
  init_player_set(BLACK);
  init_player_set(WHITE);
  modif_set(&white_init_set,14,15);
  for(int i = 0; i < HEIGHT; i++){
    printf("%d %d\n", black_init_set.ptr[i], white_init_set.ptr[i]);
  }
  check_simple_victory(15, WHITE);
  push_set(&black_current_set, 14);
  push_set(&black_current_set, 4);
  push_set(&black_current_set, 9);
  push_set(&black_current_set, 19);
  printf("%d\n", check_complex_victory(BLACK));
  */
  int s = 0;
  w = world_init();
  init_neighbors(0);
  init_player_set(1, w);
  init_player_set(2, w);
  unsigned int current_player = (rand() % (2 - 1 + 1)) + 1;
  unsigned int p = choose_random_piece_belonging_to(current_player);
  unsigned int m;
  /*
  while ((check_simple_victory(p, current_player)) && (s != 1))
  {
    p = choose_random_piece_belonging_to(current_player);
    m = choose_random_move_for_piece(w, p);
    move_piece(w, p, m);
    current_player = current_player % 2 + 1;
    s++;
  }
  */
  printf("QLQ A GAGNEEEEEEE\n");
  return 0;
}
