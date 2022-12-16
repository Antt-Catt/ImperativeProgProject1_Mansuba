#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "neighbors.h"

unsigned int neighbors_seed;


/** Initializes the relation between the neighbors, based on an
    integer `seed`. `seed` must be less than MAX_RELATIONS.
    Can be called multiple times. */
void init_neighbors(unsigned int seed)
{
  neighbors_seed = seed;

}

/** Returns the seed set by the latest call to `init_neighbors`. */
unsigned int get_neighbors_seed()
{
  return neighbors_seed;
}

/** Returns the neighbor of the place `idx`, in direction `d`, and
    UINT_MAX if there is no such neighbor (or any other kind of error) */
unsigned int get_neighbor(unsigned int idx, enum dir_t d)
{
  if (idx == UINT_MAX)
  {
    return UINT_MAX;
  }
  int i = idx / WIDTH;
  int j = idx % WIDTH;
  
  if (i == 0 && j == 0 && d == 4 && get_neighbors_seed() == 2)
  {
    return UINT_MAX;
  }
  
  if (i == 0 && j == (WIDTH - 1) && d == 2 && get_neighbors_seed() == 2)
  {
    return UINT_MAX;
  }
  
  if (i == (HEIGHT - 1) && j == 0 && d == -2 && get_neighbors_seed() == 2)
  {
    return UINT_MAX;
  }
  
  if (i == (HEIGHT - 1) && j == (WIDTH - 1) && d == -4 && get_neighbors_seed() == 2)
  {
    return UINT_MAX;
  }
  
  if (i == 0 && (d == 2 || d == 3 || d == 4))
  {
    if (get_neighbors_seed() == 2)
    {
      return idx - d + 3 + WIDTH * (HEIGHT - 1);
    }
    return UINT_MAX;
  }
  
  if (j == 0 && (d == -1 || d == -2 || d == 4))
  {
    return UINT_MAX;
  }
  
  if (i == (HEIGHT - 1) && (d == -2 || d == -3 || d == -4))
  {
    if (get_neighbors_seed() == 2)
    {
      return idx - (d + 3) - WIDTH * (HEIGHT - 1);
    }
    return UINT_MAX;
  }
  
  if (j == (WIDTH - 1) && (d == 1 || d == 2 || d == -4))
  {
    return UINT_MAX;
  }

  switch (d)
  {
  case -4:
    return idx + WIDTH + 1;
  case -3:
    return idx + WIDTH;
  case -2:
    return idx + WIDTH - 1;
  case -1:
    return idx - 1;
  case 1:
    return idx + 1;
  case 2:
    return idx - WIDTH + 1;
  case 3:
    return idx - WIDTH;
  case 4:
    return idx - WIDTH - 1;
  default:
    return UINT_MAX;
  }
}

/** Returns the list of the neighbors of the place `idx`, terminated
    by UINT_MAX.  */
struct neighbors_t get_neighbors(unsigned int idx)
{
  struct neighbors_t result;
  int s = 0;
  int k = -4;
  while (k < 5)
  {
    unsigned int n_idx = get_neighbor(idx, k);
    if (n_idx != UINT_MAX)
    {
      result.n[s].i = n_idx;
      result.n[s].d = k;
      s++;
    }
    k++;
    if (k == 0)
    {
      k++;
    }
  }
  result.n[s].i = UINT_MAX;
  result.n[s].d = 0;
  for (k = (s + 1); k < MAX_NEIGHBORS + 1; k++)
  {
    result.n[k].i = 0;
    result.n[k].d = 0;
  }
  return result;
}
