#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "movements.h"

set_t black_init_set;
set_t black_current_set;
set_t white_init_set;
set_t white_current_set;

void possible_mvts_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init)
{
  if (exist_in_set(set, idx) == UINT_MAX && idx != init)
  {
    push_set(set, idx);
  }
  int j;
  int k = 0;
  unsigned int idx_n;
  struct neighbors_t neigh_idx = get_neighbors(idx);
  while (neigh_idx.n[k].i != UINT_MAX)
  {
    j = neigh_idx.n[k].d;
    if (j == -3 || j == -1 || j == 1 || j == 3)
    {
      if (world_get_sort(w, neigh_idx.n[k].i) != 0)
      {
        idx_n = get_neighbor(neigh_idx.n[k].i, j);
        if (idx_n != UINT_MAX && world_get_sort(w, idx_n) == 0 && exist_in_set(set, idx_n) == UINT_MAX && idx_n != init)
        {
          possible_mvts_aux(set, idx_n, w, idx);
        }
      }
    }
    k++;
  }
}

set_t possible_mvts(unsigned int idx, struct world_t *w)
{
  if (world_get_sort(w, idx) == TOWER)
  {
    return possible_mvts_tower(idx, w);
  }
  if (world_get_sort(w, idx) == ELEPHANT)
  {
    return possible_mvts_elephant(idx, w);
    set_t set = init_set(0);
  }
  int j = -3;
  unsigned int idx_n;
  while (j < 4)
  {
    idx_n = get_neighbor(idx, j);
    push_set(&set, idx_n);
    /*
    if (world_get_sort(w, idx_n) == 0)
    {
    }*/
    else
    {
      idx_n = get_neighbor(idx_n, j);
      if (world_get_sort(w, idx_n) == 0)
      {
        possible_mvts_aux(&set, idx_n, w, idx);
      }
    }
    j += 2;
  }
  return set;
}

void move_piece(struct world_t *w, unsigned int p, unsigned int m)
{
  if (p != m)
  {
    unsigned int current_player = world_get(w, p);
    world_set(w, m, current_player);
    world_set_sort(w, m, world_get_sort(w, p));
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
}
