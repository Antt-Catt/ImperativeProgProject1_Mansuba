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

void init_player_set(unsigned int p)
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
	  printf("Victoire simple pour WHITE");
	}
    }
  else
    {
      if (exist_in_set(&white_init_set,idx) != UINT_MAX)
	{
	  printf("Victoire simple pour BLACK");
	}
    }
}

int main(int argc, char *argv[])
{
  argc = argc;
  argv[0] = argv[0];
  world_init();
  init_player_set(BLACK);
  init_player_set(WHITE);
  modif_set(&white_init_set,14,15);
  for(int i = 0; i < HEIGHT; i++){
    printf("%d %d\n", black_init_set.ptr[i], white_init_set.ptr[i]);
  }
  check_simple_victory(15, WHITE); 
  return 0;
}
