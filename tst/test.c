#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../src/neighbors.h"
#include "../src/geometry.h"
#include "../src/world.h"
#include "../src/set.h"

struct world_t * world_init();

int main(int argc, char* argv[])
{
  argc = argc;
  argv[0] = argv[0];
  
  printf("\n");
  //tests geometry
  int d = 4;
  int c = 2;
  int s = 1;
  printf("Tests de geometry.c :\n");
  printf("Direction nord ouest : %s\n",dir_to_string(d));
  printf("Un pion blanc sur cette place : %s\n", place_to_string(c,s));

  printf("\n");

  //tests world
  printf("Tests de world.c :\n");
  extern struct world_t w;
  world_init();
  for (int i = 0; i < WORLD_SIZE; i++){
    printf("place %d, color %d, sort %d\n", i, world_get(&w,i), world_get_sort(&w,i));
  }
  
  world_set(&w, 5, 1); 
  world_set_sort(&w, 16, 1);
  world_set(&w, 16, 2); 
  printf("place 5, color %d, sort %d\n", world_get(&w, 5), world_get_sort(&w, 5));
  printf("place 16, color %d, sort %d\n", world_get(&w, 16), world_get_sort(&w, 16));


  //tests neighbors
  printf("neighbors %d\n", get_neighbor(0,2));
  printf("neighbors %d\n", get_neighbor(0,-3));
  printf("neighbors %d\n", get_neighbor(10,-3));
  printf("neighbors %d\n", get_neighbor(14,1));

  struct neighbors_t result = get_neighbors(9);
  for(int p = 0; p < MAX_NEIGHBORS + 1; p++){
    printf("%d %d\n", result.n[p].i, result.n[p].d); 
  }
  printf("\n");
 

  set_t ens = init_set(5);
  append_set(&ens, 17);
  int x = ens.size;
  modif_set(&ens, 17, 19);
  int y = pop_set(&ens);
  int z = ens.size;
  printf("%d, %d, %d\n", x, y, z);

  return 0;

}
