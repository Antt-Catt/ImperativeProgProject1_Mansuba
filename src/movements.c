#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "movements.h"
#include "neighbors.h"
#include "achiev1.h"
#include "world.h"
#include "set.h"

set_t black_current_set;
set_t white_current_set;

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
    if (world_get_sort(w, neigh_idx.n[j].i) != 0)
    {
      idx_n = get_neighbor(idx_n, neigh_idx.n[j].d);
      if (idx_n != UINT_MAX && world_get_sort(w, idx_n) == 0 && exist_in_set(set, idx_n) == UINT_MAX && idx_n != init)
      {
        possible_mvts_aux(set, idx_n, w, init);
      }
    }
    j++;
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
  }
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
      if (idx_n != UINT_MAX && world_get_sort(w, idx_n) == 0)
      {
        possible_mvts_aux(&set, idx_n, w, idx);
      }
    }
    j++;
  }
  return set;
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
