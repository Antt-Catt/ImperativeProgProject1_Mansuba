#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "test.h"

unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p)
{
  set_t set = possible_mvts(p, w);
  if (set.size > 1)
  {
    unsigned int tmp = set.size - 1;
    int i = (rand() % (tmp - 0 + 1)) + 0;
    unsigned int x = set.ptr[i];
    delete_set(&set);
    return x;
  }
  return p;
}

void print_world(struct world_t *w)
{
  for (int i = 0; i < HEIGHT; i++)
  {
    /*if (i % WIDTH == 0 && i != 0)
    {
      printf("\n");
    }
    printf("i=%d_s=%d_c=%d\t", i, world_get_sort(w, i), world_get(w, i));*/
    for (int j = 0; j < WIDTH; j++)
    {
      if (world_get_sort(w, i*WIDTH + j) == NO_SORT)
	{
	  if (world_get(w, i*WIDTH + j) != NO_COLOR)
	    {
	      printf("X");
	    }
	  printf(".");
	}
      else if (world_get(w, i*WIDTH + j) == BLACK)
	{
	  printf("B");
	}
      else if (world_get(w, i*WIDTH + j) == WHITE)
	{
	  printf("W");
	}
      else
	{
	  printf("X");
	}
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char* argv[])
{
  argc = argc;
  argv[0] = argv[0];
  
  printf("\n");
  //tests geometry
  int d = 4;
  int c = 2;
  int s = 1;
  printf("geometry tests :\n");
  printf("Direction nord ouest : %s\n",dir_to_string(d));
  printf("Un pion blanc sur cette place : %s\n", place_to_string(c,s));

  printf("\n");
  //tests world
  printf("world tests :\n");
  //extern struct world_t w;
  struct world_t* w = world_init();
  for (int i = 0; i < WORLD_SIZE; i++){
    printf("place %d, color %d, sort %d\n", i, world_get(w,i), world_get_sort(w,i));
  }
  
  world_set(w, 5, 1); 
  world_set_sort(w, 16, 1);
  world_set(w, 16, 2); 
  printf("place 5, color %d, sort %d\n", world_get(w, 5), world_get_sort(w, 5));
  printf("place 16, color %d, sort %d\n", world_get(w, 16), world_get_sort(w, 16));
  
  printf("\n");
  //tests neighbors
  printf("neighbors tests :\n");
  printf("neighbor %d\n", get_neighbor(0,2));
  printf("neighbor %d\n", get_neighbor(0,-3));
  printf("neighbor %d\n", get_neighbor(10,-3));
  printf("neighbor %d\n", get_neighbor(14,1));

  struct neighbors_t result = get_neighbors(9);
  for(int p = 0; p < MAX_NEIGHBORS + 1; p++){
    printf("%d %d\n", result.n[p].i, result.n[p].d); 
  }

  printf("\n");
  //tests set
  printf("set tests :\n");
  set_t ens = init_set(0);
  push_set(&ens, 17);
  print_set(&ens);
  //int x = ens.size;
  modif_set(&ens, 17, 19);
  print_set(&ens);
  push_set(&ens, 7);
  push_set(&ens, 12);
  push_set(&ens, 43);
  push_set(&ens, 5);
  print_set(&ens);
  printf("set size = %d\n", ens.size);
  printf("43 is in idx %d\n", exist_in_set(&ens, 43));
  printf("last elt is %d\n\n", pop_set(&ens));
  print_set(&ens);
  printf("set size = %d\n\n", ens.size);
  delete_from_set(&ens, 12);
  print_set(&ens);
  printf("final set size = %d\n", ens.size);
  
  printf("\n");
  //tests movements
  printf("movements tests :\n");
  w = world_init();
  world_set_sort(w, 6, 1);
  world_set(w, 6, 2);
  world_set_sort(w, 7, 1);
  world_set(w, 7, 1);
  world_set_sort(w, 13, 1);
  world_set(w, 13, 1);
  world_set_sort(w, 11, 2);
  world_set(w, 11, 2);
  world_set_sort(w, 17, 1);
  world_set(w, 17, 1);
  print_world(w);
  set_t set = possible_mvts(6, w);
  print_set(&set);
  move_piece(w, 6, set.ptr[2]);
  print_world(w);
  
  
  return 0;

}
