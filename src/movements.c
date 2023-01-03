#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "movements.h"

set_t black_init_set;
set_t black_current_set;
set_t white_init_set;
set_t white_current_set;

// set_t possible_directions;

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
    if (exist_in_set(&drts, j + 4) != UINT_MAX && world_get(w, idx_n) != 0)
    {
      idx_n = get_neighbor(idx_n, j);
      if (idx_n != UINT_MAX && world_get(w, idx_n) == 0 && idx_n != init)
      {
	possible_mvts_aux(set, idx_n, w, idx);
      }
      else if (idx_n != UINT_MAX && world_get(w, idx_n) != world_get(w, init) && idx_n != init && achiev3 != 0)
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
  set_t set = init_set(0);
  set_t drts = possible_drts();
  if (idx != UINT_MAX)
  {
    if (world_get_sort(w, idx) == TOWER)
    {
      delete_set(&drts);
      delete_set(&set);
      return possible_mvts_tower(idx, w);
    }
    if (world_get_sort(w, idx) == ELEPHANT)
    {
      delete_set(&drts);
      delete_set(&set);
      return possible_mvts_elephant(idx, w);
    }
    int j = 0;
    unsigned int idx_n;
    while (drts.size != 0)
    {
      j = pop_set(&drts) - 4;
      idx_n = get_neighbor(idx, j);
      if (idx_n != UINT_MAX)
      {
      char next = 0;
      if (world_get(w, idx_n) == 0)
      {
	push_set(&set, idx_n);
	next = 1;
      }
      else if (achiev3 != 0 && world_get(w, idx_n) != world_get(w, idx))
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
	else if (achiev3 != 0 && idx_n != UINT_MAX && world_get(w, idx_n) != world_get(w, idx))
        {
	  push_set(&set, idx_n);
        }
      }
      }      
    }
  }
  delete_set(&drts);
  return set;
}

unsigned int move_piece(struct world_t *w, unsigned int p, unsigned int m)
{
  if (p != m){
    unsigned int player_in_p = world_get(w, p);

    // for achiev3
    unsigned int player_in_m = world_get(w, m);
    if (player_in_m != 0 && achiev3 == 0)
    {
      // stop function, cant move piece to an occupied place if achiev3 conditions not in place
      return 0;
    }
    else if (player_in_m != 0 && player_in_p != player_in_m)
    {
      printf("oui\n");
      unsigned int tmp = imprison(m, w);
      if (tmp == UINT_MAX)
      {
	printf("yes\n");
        // imprisoning didnt work, we cant put p in m then
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

set_t achiev4_function(set_t *set, unsigned int player)
{
  unsigned int tmp;
  set_t result = init_set(0);
  if (player == BLACK)
  {
    tmp = 0;
    for (int i = 0; i < (*set).size; i++)
    {
    // we look for (*set).ptr[i] % WIDTH maximized for player black (moving >>)
      if ((*set).ptr[i] % WIDTH > tmp)
      {
        tmp = (*set).ptr[i] % WIDTH;
      }
    }
    for (int i = 0; i < (*set).size; i++)
    {
      if ((*set).ptr[i] % WIDTH == tmp)
      {
        push_set(&result, (*set).ptr[i]);
      }
    }
  }
  else if (player == WHITE)
  {
    tmp = WIDTH;
    for (int i = 0; i < (*set).size; i++)
    {
      // we look for (*set).ptr[i] % WIDTH minimized for player white (moving <<)
      if ((*set).ptr[i] % WIDTH < tmp)
      {
        tmp = (*set).ptr[i] % WIDTH;
      }
    }
    for (int i = 0; i < (*set).size; i++)
    {
      if ((*set).ptr[i] % WIDTH == tmp)
      {
        push_set(&result, (*set).ptr[i]);
      }
    }
  }
  return result;
  }
