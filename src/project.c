#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "geometry.h"
#include "world.h"
#include "neighbors.h"
#include "set.h"

set_t black_init_set;
set_t black_current_set;

set_t white_init_set;
set_t white_current_set;

extern struct world_t w;

void mvt_possibles_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init)
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
                    mvt_possibles_aux(set, idx_n, w, init);
                }
            }
        }
        j++;
    }
}

set_t mvt_possibles(unsigned int idx, struct world_t *w)
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
                mvt_possibles_aux(&set, idx_n, w, idx);
            }
        }
        j++;
    }
    return set;
}

void init_player_set(unsigned int p, struct world_t * w)
{
  for (int i = 0; i < HEIGHT; i++)
  {
    if (p == BLACK)
    {
      world_set(&w, WIDTH * i, p);
      push_set(&black_init_set, WIDTH * i);
    }
    else
    {
      world_set(&w, WIDTH * i + HEIGHT, p);
      push_set(&white_init_set, WIDTH * i + HEIGHT);
    }
  }
}

void check_simple_victory(unsigned int idx, unsigned int p)
{
  if (p == 2)
    {
      if (exist_in_set(&black_init_set,idx) != UINT_MAX)
	{
	  printf("Victoire simple pour WHITE\n");
	}
    }
  else
    {
      if (exist_in_set(&white_init_set,idx) != UINT_MAX)
	{
	  printf("Victoire simple pour BLACK\n");
	}
    }
}

int main(int argc, char *argv[])
{
  /*argc = argc;
  argv[0] = argv[0];
  world_init();
  init_player_set(BLACK);
  init_player_set(WHITE);
  modif_set(&white_init_set,14,15);
  for(int i = 0; i < HEIGHT; i++){
    printf("%d %d\n", black_init_set.ptr[i], white_init_set.ptr[i]);
  }
  check_simple_victory(15, WHITE);*/
  return 0;
}
