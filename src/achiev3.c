// some includes should be removed
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "achiev3.h"

unsigned int achiev3;
set_t black_prison;
set_t white_prison;

extern set_t black_init_set;
extern set_t black_current_set;
extern set_t white_init_set;
extern set_t white_current_set;

unsigned int imprison(unsigned int idx, struct world_t *w)
{
  
  if (exist_in_set(&black_init_set, idx) == UINT_MAX && exist_in_set(&white_init_set, idx) == UINT_MAX)
  {
    unsigned int player = world_get(w, idx);
    unsigned int sort = world_get_sort(w, idx);
    // piece disappears from world
    world_set(w, idx, 0);
    world_set_sort(w, idx, 0);
    // piece (idx, player, sort) stored in prison
    if (player == BLACK)
    {
      push_set(&black_prison, idx);
      push_set(&black_prison, sort);
      print_set(&black_prison);
    }
    else if (player == WHITE)
    {
      push_set(&white_prison, idx);
      push_set(&white_prison, sort);
      print_set(&white_prison);
    }
    return 0;
  }
  return UINT_MAX;
}

unsigned int escape(unsigned int player, struct world_t *w)
{
    unsigned int idx;
    unsigned int tmp;
    unsigned int sort;
    srand(time(NULL));
    if (player == BLACK)
    {
        if (black_prison.size < 2)
        {
            return UINT_MAX;
        }
        // taking last imprisoned piece, can be changed later
        idx = black_prison.ptr[black_prison.size - 2];
        sort = black_prison.ptr[black_prison.size - 1];
        // to make sure place is empty
        tmp = world_get(w, idx);
        if (tmp != 0)
        {
            return UINT_MAX;
        }
        // to achieve 50% probability
        tmp = (rand() % (2 - 1 + 1)) + 1;
        if (tmp != 2)
        {
            return 1;
        }
        world_set(w, idx, player);
        world_set_sort(w, idx, sort);
        pop_set(&black_prison);
        pop_set(&black_prison);
        return 0;
    }
    else if (player == BLACK)
    {
        if (white_prison.size < 2)
        {
            return UINT_MAX;
        }
        idx = white_prison.ptr[white_prison.size - 2];
        sort = white_prison.ptr[white_prison.size - 1];
        tmp = world_get(w, idx);
        if (tmp != 0)
        {
            return UINT_MAX;
        }
        tmp = (rand() % (2 - 1 + 1)) + 1;
        if (tmp != 2)
        {
            return 1;
        }
        world_set(w, idx, player);
        world_set_sort(w, idx, sort);
        pop_set(&white_prison);
        pop_set(&white_prison);
        return 0;
    }
    return UINT_MAX;
}
