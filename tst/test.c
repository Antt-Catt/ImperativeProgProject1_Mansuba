#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "test.h"

/*unsigned int choose_random_move_for_piece(struct world_t *w, unsigned int p)
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
  printf("\n");
  for (int i = 0; i < HEIGHT; i++)
  {
    if (get_neighbors_seed() == 1 && i%2 == 1)
    {
      printf("\t");
    }
    for (int j = 0; j < WIDTH; j++)
    {
      if (world_get_sort(w, i * WIDTH + j) == NO_SORT)
      {
        printf(".\t\t");
      }
      else if (world_get(w, i * WIDTH + j) == BLACK)
      {
        printf("B(%d)\t\t", world_get_sort(w, i * WIDTH + j));
      }
      else if (world_get(w, i * WIDTH + j) == WHITE)
      {
        printf("W(%d)\t\t", world_get_sort(w, j + i * WIDTH));
      }
      else
      {
        printf("X");
      }
    }
    printf("\n\n");
  }
  printf("\n====================================\n\n");
}*/

int main(int argc, char* argv[])
{
  argc = argc;
  argv[0] = argv[0];
  init_neighbors(0);
  
  printf("\n");
  //tests geometry
  printf("geometry tests :\n");
  printf("North west direction : %s\n",dir_to_string(4));
  printf("A white pawn in this place : %s\n", place_to_string(2,1));
  printf("A black elephant in this place : %s\n", place_to_string(1,3));
  printf("A white tower in this place : %s\n", place_to_string(2,2));

  printf("\n\n");
  //tests world
  printf("world tests :\n");
  printf("world init :\n");
  struct world_t* w = world_init();
  for (int i = 0; i < WORLD_SIZE; i++){
    printf("place %d, color %d, sort %d\n", i, world_get(w,i), world_get_sort(w,i));
  }
  
  world_set(w, 5, 1); 
  world_set_sort(w, 16, 1);
  world_set(w, 16, 2);
  printf("\nset place 5 at color 1\n");
printf("place 5, color %d, sort %d\n", world_get(w, 5), world_get_sort(w, 5));
  printf("set place 16 at color 2 and sort 1\n");
  printf("place 16, color %d, sort %d\n", world_get(w, 16), world_get_sort(w, 16));
  
  printf("\n\n");
  //tests neighbors
  printf("neighbors tests :\n");
  printf("neighbor of %d in direction %s is %d ; expected -1\n", 0, dir_to_string(2), get_neighbor(0, 2));
  printf("neighbor of %d in direction %s is %d ; expected 5\n", 0, dir_to_string(-3), get_neighbor(0, -3));
  printf("neighbor of %d in direction %s is %d ; expected 6\n", 12, dir_to_string(4), get_neighbor(12, 4));
  printf("neighbor of %d in direction %s is %d ; expected -1\n", 14, dir_to_string(1), get_neighbor(14, 1));
  printf("\n");
  
  struct neighbors_t result = get_neighbors(9);
  printf("neighbors of 9 in all directions are ");
  for(int p = 0; p < MAX_NEIGHBORS + 1; p++){
    printf("%d ", result.n[p].i);  
  }
  printf("\nexpected 14 13 8 4 3 -1 0 0 0\n");
  printf("\n");

  result = get_neighbors(15);
  printf("neighbors of 15 in all directions are ");
  for(int p = 0; p < MAX_NEIGHBORS + 1; p++){
    printf("%d ", result.n[p].i);  
  }
  printf("\nexpected 16 11 10 -1 0 0 0 0 0\n");
  printf("\n");

  printf("\n");
  //tests set
  printf("set tests :\n");
  set_t ens = init_set(0);
  push_set(&ens, 17);
  print_set(&ens);
  printf("{ 17 } expected\n\n");
  //int x = ens.size;
  modif_set(&ens, 17, 19);
  print_set(&ens);
  printf("{ 19 } expected\n\n");
  push_set(&ens, 7);
  push_set(&ens, 12);
  push_set(&ens, 43);
  push_set(&ens, 15);
  print_set(&ens);
  printf("{ 19 7 12 43 15 } expected\n\n");
  printf("set size = %d ; expected 5\n\n", ens.size);
  printf("43 is in idx %d ; expected 3\n\n", exist_in_set(&ens, 43));
  printf("last elt is %d ; expected 15\n\n", pop_set(&ens));
  print_set(&ens);
  printf("{ 19 7 12 43 } expected\n");
  printf("set size = %d ; expected 4\n\n", ens.size);
  delete_from_set(&ens, 12);
  print_set(&ens);
  printf("{ 19 7 43 } expected\n");
  printf("final set size = %d ; expected 3\n\n", ens.size);
  
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
  world_set_sort(w, 11, 1);
  world_set(w, 11, 2);
  //world_set_sort(w, 17, 1);
  //world_set(w, 17, 1);
  print_world(w);
  set_t set = possible_mvts(6, w);
  printf("possible movements for piece 6 :\n");
  print_set(&set);
  printf("{ 1 8 18 16 5 } expected\n");
  move_piece(w, 6, set.ptr[2]);
  print_world(w);
  printf("%d\n", HEIGHT);
  
  //tests achiev2
  init_neighbors(2);
  printf("neighbor of %d in dir %s is %d ; expected 16\n", 0, dir_to_string(2), get_neighbor(0,2));
  printf("neighbor of %d in direction %s is %d ; expected 19\n", 0, dir_to_string(4), get_neighbor(0,4));
  printf("neighbor of %d in direction %s is %d ; expected 18\n", 3, dir_to_string(3), get_neighbor(3,3));
  printf("neighbor of %d in direction %s is %d ; expected 15\n", 4, dir_to_string(2), get_neighbor(4,2));
  printf("neighbor of %d in direction %s is %d ; expected 4\n", 15, dir_to_string(-2), get_neighbor(15,-2));
  printf("\n");
  
  result = get_neighbors(9);
  printf("neighbors of 9 in all directions are ");
  for(int p = 0; p < MAX_NEIGHBORS + 1; p++){
    if (result.n[p].i != UINT_MAX)
    {
      printf("%d ", result.n[p].i); 
    }
  }
  printf("\nexpected 10 14 13 8 5 0 4 3\n");
  printf("\n");
  
  result = get_neighbors(17);
  printf("neighbors of 17 in all directions are ");
  for(int p = 0; p < MAX_NEIGHBORS + 1; p++){
    printf("%d ", result.n[p].i); 
  }
  printf("\nexpected 3 2 1 16 18 13 12 11 -1\n");
  return 0;

}
