#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "movements.h"

set_t black_init_set;
set_t black_current_set;
set_t white_init_set;
set_t white_current_set;
//set_t possible_directions;

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

void possible_mvts_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init)
{
  printf("0 %d\t", idx);
  if (exist_in_set(set, idx) == UINT_MAX && idx != init)
  {
    push_set(set, idx);
  }
  int j;
  int k = 0;
  unsigned int idx_n;
  set_t drts = possible_drts();
  struct neighbors_t neigh_idx = get_neighbors(idx);
  while (neigh_idx.n[k].i != UINT_MAX)
  {
    j = neigh_idx.n[k].d;
    idx_n = neigh_idx.n[k].i;
    if (exist_in_set(&drts, j + 4) != UINT_MAX)
    {
      {
        if (idx_n != UINT_MAX && world_get_sort(w, idx_n) != 0)
        {
          idx_n = get_neighbor(idx_n, j);
          if (idx_n != UINT_MAX && world_get_sort(w, idx_n) == 0 && idx_n != init)
          {
            possible_mvts_aux(set, idx_n, w, idx);
          }
        }
      }
    }
    k++;
  }
  delete_set(&drts);
}

set_t possible_mvts(unsigned int idx, struct world_t *w)
{
  set_t set = init_set(0);
  set_t drts = possible_drts();
  if (idx != UINT_MAX)
  {
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
    while (drts.size != 0)
    {
      j = pop_set(&drts) - 4;
      idx_n = get_neighbor(idx, j);
      if (idx_n != UINT_MAX && world_get_sort(w, idx_n) == 0)
      {
        push_set(&set, idx_n);
      }
      else
      {
        idx_n = get_neighbor(idx_n, j);
        if (idx_n != UINT_MAX && world_get_sort(w, idx_n) == 0)
        {
          possible_mvts_aux(&set, idx_n, w, idx);
        }
      }
    }
  }
  delete_set(&drts);
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
