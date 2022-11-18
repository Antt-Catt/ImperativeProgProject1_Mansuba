#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../src/neighbors.h"
#include "../src/geometry.h"
#include "../src/world.h"

struct world_t * world_init();

int main(int argc, char* argv[])
{
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
  printf("%d\n", world_get(world_init(),2));

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
  return 0;
}
