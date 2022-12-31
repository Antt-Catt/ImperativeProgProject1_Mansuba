#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "test.h"

void test_geometry()
{
  printf("North west direction : %s\n", dir_to_string(4));
  printf("A white pawn in this place : %s\n", place_to_string(2, 1));
  printf("A black elephant in this place : %s\n", place_to_string(1, 3));
  printf("A white tower in this place : %s\n", place_to_string(2, 2));
}

void test_world()
{
  printf("world init :\n");
  struct world_t *w = world_init();
  for (int i = 0; i < WORLD_SIZE; i++)
  {
    printf("place %d, color %d, sort %d\n", i, world_get(w, i), world_get_sort(w, i));
  }

  world_set(w, 5, 1);
  world_set_sort(w, 16, 1);
  world_set(w, 16, 2);
  printf("\nset place 5 at color 1\n");
  printf("place 5, color %d, sort %d\n", world_get(w, 5), world_get_sort(w, 5));
  printf("set place 16 at color 2 and sort 1\n");
  printf("place 16, color %d, sort %d\n", world_get(w, 16), world_get_sort(w, 16));
}

void test_neighbors()
{
  printf("neighbor of %d in direction %s is %d ; expected -1\n", 0, dir_to_string(2), get_neighbor(0, 2));
  printf("neighbor of %d in direction %s is %d ; expected 5\n", 0, dir_to_string(-3), get_neighbor(0, -3));
  printf("neighbor of %d in direction %s is %d ; expected 6\n", 12, dir_to_string(4), get_neighbor(12, 4));
  printf("neighbor of %d in direction %s is %d ; expected -1\n", 14, dir_to_string(1), get_neighbor(14, 1));
  printf("\n");

  struct neighbors_t result = get_neighbors(9);
  printf("neighbors of 9 in all directions are ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf("\nexpected 14 13 8 4 3 -1 0 0 0\n\n");

  result = get_neighbors(15);
  printf("neighbors of 15 in all directions are ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf("\nexpected 16 11 10 -1 0 0 0 0 0\n\n");

  result = get_neighbors(7);
  printf("neighbors of 7 in all directions are ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf("\nexpected 13 12 11 6 8 3 2 1 -1\n");
}

void test_set()
{
  set_t set = init_set(0);
  push_set(&set, 17);
  print_set(&set);
  printf("{ 17 } expected\n\n");
  modif_set(&set, 17, 19);
  print_set(&set);
  printf("{ 19 } expected\n\n");
  push_set(&set, 7);
  push_set(&set, 12);
  push_set(&set, 43);
  push_set(&set, 15);
  print_set(&set);
  printf("{ 19 7 12 43 15 } expected\n\n");
  printf("set size = %d ; expected 5\n\n", set.size);
  printf("43 is in idx %d ; expected 3\n\n", exist_in_set(&set, 43));
  printf("last elt is %d ; expected 15\n\n", pop_set(&set));
  print_set(&set);
  printf("{ 19 7 12 43 } expected\n");
  printf("set size = %d ; expected 4\n\n", set.size);
  delete_from_set(&set, 12);
  print_set(&set);
  printf("{ 19 7 43 } expected\n");
  printf("final set size = %d ; expected 3\n", set.size);
  delete_set(&set);
}

void test_movements()
{
  struct world_t* w = world_init();
  world_set_sort(w, 6, 1);
  world_set(w, 6, 2);
  world_set_sort(w, 7, 1);
  world_set(w, 7, 1);
  world_set_sort(w, 13, 1);
  world_set(w, 13, 1);
  world_set_sort(w, 11, 1);
  world_set(w, 11, 2);
  print_world(w);
  set_t set = possible_mvts(6, w);
  printf("possible movements for piece 6 :\n");
  print_set(&set);
  printf("{ 1 8 18 16 5 } expected\n");
  move_piece(w, 6, set.ptr[2]);
  print_world(w);
  delete_set(&set);

  world_set_sort(w, 8, 1);
  world_set(w, 8, 2);
  world_set_sort(w, 18, 0);
  world_set(w, 18, 0);
  world_set_sort(w, 16, 1);
  world_set(w, 16, 1);
  world_set_sort(w, 17, 1);
  world_set(w, 17, 2);
  print_world(w);
  set = possible_mvts(16, w);
  printf("possible movements for piece 16 :\n");
  print_set(&set);
  printf("{ 18 15 6 } expected\n");
  move_piece(w, 16, set.ptr[0]);
  print_world(w);
  delete_set(&set);

  world_set_sort(w, 6, 0);
  world_set(w, 6, 0);
  world_set_sort(w, 8, 0);
  world_set(w, 8, 0);
  world_set_sort(w, 7, 0);
  world_set(w, 7, 0);
  world_set_sort(w, 1, 1);
  world_set(w, 1, 2);
  world_set_sort(w, 0, 1);
  world_set(w, 0, 1);
  world_set_sort(w, 3, 1);
  world_set(w, 3, 2);
  world_set_sort(w, 9, 1);
  world_set(w, 9, 1);
  world_set_sort(w, 5, 1);
  world_set(w, 5, 2);
  print_world(w);
  set = possible_mvts(0, w);
  printf("possible movements for piece 0 :\n");
  print_set(&set);
  printf("{ 2 4 14 12 10 } expected\n");
  move_piece(w, 0, set.ptr[4]);
  print_world(w);
  delete_set(&set);
}

void test_game()
{
  struct world_t * w = world_init();
  init_game(w, 0, 0);
  printf("the game is initialized :\n");
  print_world(w);
  print_set(&black_init_set);
  print_set(&black_current_set);
  printf("{ 0 5 10 15 } expected (black pieces)\n");
  print_set(&white_init_set);
  print_set(&white_current_set);
  printf("{ 4 9 14 19 } expected (white pieces)\n");
  print_set(&black_prison);
  printf("{ } expected\n");

  printf("BLACK simple victory on place %d : %d ; expected 0\n", black_current_set.ptr[3], check_simple_victory(black_current_set.ptr[3], BLACK));
  
  move_piece(w, 4, 12);
  move_piece(w, 10, 4);

  print_world(w);

  print_set(&white_current_set);
  printf("{ 12 9 14 19 } expected (white pieces)\n");
  print_set(&black_current_set);
  printf("{ 0 5 4 15 } expected (black pieces)\n");

  srand(time(NULL));
  
  printf("\nrandom BLACK piece : %d\n", choose_random_piece_belonging_to(BLACK));
  printf("random move for WHITE's 12th piece : %d\n\n", choose_random_move_for_piece(w, 12));

  printf("WHITE simple victory on place %d : %d ; expected 0\n", white_current_set.ptr[0], check_simple_victory(white_current_set.ptr[0], WHITE));
  printf("BLACK simple victory on place %d : %d ; expected 1\n", black_current_set.ptr[2], check_simple_victory(black_current_set.ptr[2], BLACK));
  printf("BLACK complex victory : %d ; expected 0\n\n", check_complex_victory(BLACK));
  
  print_set(&black_current_set);
  printf("{ 0 5 15 } expected (black pieces)\n");
  
  move_piece(w, 9, 1);
  move_piece(w, 14, 10);
  move_piece(w, 19, 3);
  move_piece(w, 0, 19);
  move_piece(w, 5, 9);
  move_piece(w, 15, 14);

  print_world(w);
  
  printf("WHITE simple victory on place %d : %d ; expected 2\n", white_current_set.ptr[2], check_simple_victory(white_current_set.ptr[2], WHITE));
  printf("WHITE complex victory : %d ; expected 0\n", check_complex_victory(WHITE));

  print_set(&white_current_set);
  printf("{ 12 1 3 } expected (white pieces)\n");

  printf("BLACK complex victory : %d ; expected 1\n", check_complex_victory(BLACK));

  print_set(&black_current_set);
  printf("{ } expected (black pieces)\n");
  
  delete_set(&black_init_set);
  delete_set(&black_current_set);
  delete_set(&white_init_set);
  delete_set(&white_current_set);
}

void test_achiev1()
{

}

void test_achiev2()
{
  init_neighbors(2);
  printf("neighbor of %d in dir %s is %d ; expected 16\n", 0, dir_to_string(2), get_neighbor(0, 2));
  printf("neighbor of %d in direction %s is %d ; expected -1\n", 0, dir_to_string(4), get_neighbor(0, 4));
  printf("neighbor of %d in direction %s is %d ; expected 18\n", 3, dir_to_string(3), get_neighbor(3, 3));
  printf("neighbor of %d in direction %s is %d ; expected -1\n", 4, dir_to_string(2), get_neighbor(4, 2));
  printf("neighbor of %d in direction %s is %d ; expected -1\n", 15, dir_to_string(-2), get_neighbor(15, -2));
  printf("neighbor of %d in direction %s is %d ; expected -1\n", 10, dir_to_string(-2), get_neighbor(10, -2));
  printf("neighbor of %d in direction %s is %d ; expected 2\n", 16, dir_to_string(-4), get_neighbor(16, -4));
  printf("\n");

  struct neighbors_t result = get_neighbors(9);
  printf("neighbors of 9 in all directions are ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    if (result.n[p].i != UINT_MAX)
    {
      printf("%d ", result.n[p].i);
    }
  }
  printf("\nexpected 10 14 13 8 5 0 4 3\n");
  printf("\n");

  result = get_neighbors(17);
  printf("neighbors of 17 in all directions are ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf("\nexpected 3 2 1 16 18 13 12 11 -1\n");
}

void test_achiev3()
{
  /*struct world_t * w = world_init();
  print_world(w);
  achiev3 = 1;
  move_piece(w, 11, 7);
  print_world(w);
  print_set(&black_prison);
  move_piece(w, 7, 8);
  escape(BLACK, w);
  print_world(w);
  print_set(&black_prison);*/
}

int main(int argc, char *argv[])
{
  argc = argc;
  argv[0] = argv[0];
  init_neighbors(0);

  achiev3 = 0;
  achiev4 = 0;
  init_neighbors(0);
  
  printf("\n");
  // tests geometry
  printf("geometry tests :\n");
  test_geometry();
  printf("\n\n");
  
  // tests world
  printf("world tests :\n");
  test_world();
  printf("\n\n");
  
  // tests neighbors
  printf("neighbors tests :\n");
  test_neighbors();
  printf("\n\n");
  
  // tests set
  printf("set tests :\n");
  test_set();
  printf("\n\n");
  
  // tests movements
  printf("movements tests :\n");
  test_movements();
  printf("\n\n");

  // tests game
  printf("game tests :\n");
  test_game();
  printf("\n\n");

  // tests achiev1
  printf("achiev1 tests :\n");
  test_achiev1();
  printf("\n\n");

  
  // tests achiev2
  printf("achiev 2 tests :\n");
  test_achiev2();
  printf("\n\n");
  
  // tests achiev3
  printf("achiev3 tests : \n");
  test_achiev3();
  printf("\n\n");

  
  return 0;
}
