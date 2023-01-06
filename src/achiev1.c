#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "achiev1.h"

set_t possible_mvts_tower(unsigned int idx, struct world_t *w)
{
  set_t set = init_set(0);
  int j = -3;
  unsigned int idx_n;
  while (j < 4)
  {
    idx_n = get_neighbor(idx, j);
    while (idx_n != UINT_MAX && world_get(w, idx_n) != world_get(w, idx))
    {
      if (world_get(w, idx_n) != 0 && exist_in_set(&black_init_set, idx_n) == UINT_MAX && exist_in_set(&white_init_set, idx_n) == UINT_MAX)
      {
        push_set(&set, idx_n);
        idx_n = UINT_MAX;
        // le break ici ne marchait pas, cest pourquoi on avait ce probleme avec les tours
      }
      else if (world_get(w, idx_n) == 0)
      {
        push_set(&set, idx_n);
        idx_n = get_neighbor(idx_n, j);
      }
      else
      {
        idx_n = UINT_MAX;
      }
      printf("%d\n", idx_n);
    }
    j += 2;
  }
  printf("psbl mvts for %d\n", idx);
  print_set(&set);
  return set;
}

set_t possible_mvts_elephant(unsigned int idx, struct world_t *w)
{
  set_t set = init_set(0);
  int j = -3;
  unsigned int idx_n;
  while (j < 4)
  {
    idx_n = get_neighbor(get_neighbor(idx, j), j);
    if (idx_n != UINT_MAX && world_get(w, idx_n) != world_get(w, idx))
    {
      if ((world_get(w, idx_n) != 0 && exist_in_set(&black_init_set, idx_n) == UINT_MAX && exist_in_set(&white_init_set, idx_n) == UINT_MAX) || world_get(w, idx_n) == 0)
      {
        push_set(&set, idx_n);
      }
    }
    j += 2;
  }
  j = -4;
  while (j < 5)
  {
    idx_n = get_neighbor(idx, j);
    if (idx_n != UINT_MAX && world_get(w, idx_n) == world_get(w, idx))
    {
      if ((world_get(w, idx_n) != 0 && exist_in_set(&black_init_set, idx_n) && exist_in_set(&white_init_set, idx_n)) || world_get(w, idx_n) == 0)
      {
        push_set(&set, idx_n);
      }
    }
    j += 2;
    if (j == 0)
    {
      j += 2;
    }
  }
  return set;
}
