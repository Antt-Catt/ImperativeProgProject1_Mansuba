#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "movements.h"

set_t black_init_set;
set_t black_current_set;
set_t white_init_set;
set_t white_current_set;

set_t possible_drts()
{
  set_t set = init_set(0);
  if (get_neighbors_seed() == 0)
  {
    for (int i = -3; i < 4; i += 2)
    {
      push_set(&set, i + 4);
    }
  }
  else if (get_neighbors_seed() == 1)
  {
    for (int i = -3; i < 4; i++)
    {
      if (i != 0)
      {
        push_set(&set, i + 4);
      }
    }
  }
  return set;
}

void possible_mvts_aux(set_t *set, unsigned int idx_n, struct world_t *w, unsigned int idx)
{
  if (exist_in_set(set, idx_n) == UINT_MAX && idx_n != idx)
  {
    push_set(set, idx_n);
  }
  int j;
  int k = 0;
  set_t drts = possible_drts();
  struct neighbors_t neigh_idx = get_neighbors(idx_n);
  while (neigh_idx.n[k].i != UINT_MAX)
  {
    j = neigh_idx.n[k].d;
    idx_n = neigh_idx.n[k].i;
    if (exist_in_set(&drts, j + 4) != UINT_MAX && world_get(w, idx_n) != 0)
    {
      idx_n = get_neighbor(idx_n, j);
      if (idx_n != UINT_MAX && world_get(w, idx_n) == 0 && idx_n != idx && exist_in_set(set, idx_n) == UINT_MAX)
      {
        possible_mvts_aux(set, idx_n, w, idx);
      }
      else if (idx_n != UINT_MAX && world_get(w, idx_n) != world_get(w, idx) && idx_n != idx && achiev3 != 0 && exist_in_set(&black_init_set, idx_n) == UINT_MAX && exist_in_set(&white_init_set, idx_n) == UINT_MAX)
      {
        push_set(set, idx_n);
      }
    }
    k++;
  }
  delete_set(&drts);
}

set_t possible_mvts(unsigned int idx, struct world_t *w)
{
  if (idx == UINT_MAX)
  {
    return init_set(0);
  }
  if (world_get_sort(w, idx) == TOWER)
  {
    return possible_mvts_tower(idx, w);
  }
  if (world_get_sort(w, idx) == ELEPHANT)
  {
    return possible_mvts_elephant(idx, w);
  }
  int j = 0;
  unsigned int idx_n;
  set_t set = init_set(0);
  set_t drts = possible_drts();
  while (drts.size != 0)
  {
    j = pop_set(&drts) - 4;
    idx_n = get_neighbor(idx, j);
    if (idx_n != UINT_MAX)
    {
      unsigned int next = 0;
      if (world_get(w, idx_n) == 0)
      {
        push_set(&set, idx_n);
        next = 1;
      }
      else if (achiev3 != 0 && world_get(w, idx_n) != world_get(w, idx) && exist_in_set(&black_init_set, idx_n) == UINT_MAX && exist_in_set(&white_init_set, idx_n) == UINT_MAX)
      {
        push_set(&set, idx_n);
      }
      if (next == 0)
      {
        idx_n = get_neighbor(idx_n, j);
        if (idx_n != UINT_MAX && world_get(w, idx_n) == 0)
        {
          possible_mvts_aux(&set, idx_n, w, idx);
        }
        else if (achiev3 != 0 && idx_n != UINT_MAX && world_get(w, idx_n) != world_get(w, idx) && exist_in_set(&black_init_set, idx_n) == UINT_MAX && exist_in_set(&white_init_set, idx_n) == UINT_MAX)
        {
          push_set(&set, idx_n);
        }
      }
    }
  }
  delete_set(&drts);
  unsigned int player = world_get(w, idx);
  if (achiev4 != 0)
  {
    set = achiev4_mvts(&set, player);
  }
  return set;
}

unsigned int move_piece(struct world_t *w, unsigned int p, unsigned int m)
{
  if (p != m && p != UINT_MAX && m != UINT_MAX)
  {
    unsigned int player_in_p = world_get(w, p);
    unsigned int player_in_m = world_get(w, m);
    if (player_in_m != 0 && achiev3 == 0)
    {
      return 0;
    }
    else if (player_in_m != 0 && player_in_p != player_in_m)
    {
      unsigned int tmp = imprison(m, w);
      if (tmp == UINT_MAX)
      {
        return 0;
      }
    }
    world_set(w, m, player_in_p);
    world_set_sort(w, m, world_get_sort(w, p));
    if (player_in_p == BLACK)
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
  return 0;
}
