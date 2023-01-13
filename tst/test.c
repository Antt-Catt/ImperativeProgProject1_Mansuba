#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "victory.h"
#include "interface.h"

void test_geometry()
{
  printf("North west direction: %s\n", dir_to_string(4));
  printf("A white pawn in this place: %s\n", place_to_string(2, 1));
  printf("A black elephant in this place: %s\n", place_to_string(1, 3));
  printf("A white tower in this place: %s\n", place_to_string(2, 2));
}

void test_world()
{
  printf("World init :\n");
  struct world_t *w = world_init();
  for (int i = 0; i < WORLD_SIZE; i++)
  {
    printf("Place %d, Color %d, Sort %d\n", i, world_get(w, i), world_get_sort(w, i));
  }

  world_set(w, 5, 1);
  world_set_sort(w, 16, 1);
  world_set(w, 16, 2);
  printf("\nSet Place 5 at Color 1\n");
  printf("Place 5, Color %d, Sort %d\n", world_get(w, 5), world_get_sort(w, 5));
  printf("Set Place 16 at Color 2 and Sort 1\n");
  printf("Place 16, Color %d, Sort %d\n", world_get(w, 16), world_get_sort(w, 16));
}

void test_neighbors()
{
  printf("Neighbor of %d in direction %s: %d, expected: -1\n", 0, dir_to_string(2), get_neighbor(0, 2));
  printf("Neighbor of %d in direction %s: %d, expected: 5\n", 0, dir_to_string(-3), get_neighbor(0, -3));
  printf("Neighbor of %d in direction %s: %d, expected: 6\n", 12, dir_to_string(4), get_neighbor(12, 4));
  printf("Neighbor of %d in direction %s: %d, expected: -1\n", 14, dir_to_string(1), get_neighbor(14, 1));
  printf("\n");

  struct neighbors_t result = get_neighbors(9);
  printf("Neighbors of 9 in all directions: ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf(", epected: 14 13 8 4 3 -1 0 0 0\n\n");

  result = get_neighbors(15);
  printf("Neighbors of 15 in all directions: ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf(", expected 16 11 10 -1 0 0 0 0 0\n\n");

  result = get_neighbors(7);
  printf("Neighbors of 7 in all directions: ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf(", expected 13 12 11 6 8 3 2 1 -1\n");
}

void test_set()
{
  set_t set = init_set(0);
  push_set(&set, 17);
  print_set(&set);
  printf("Expected: { 17 }\n\n");
  modif_set(&set, 17, 19);
  print_set(&set);
  printf("Expected: { 19 }\n\n");
  push_set(&set, 7);
  push_set(&set, 12);
  push_set(&set, 43);
  push_set(&set, 15);
  print_set(&set);
  printf("Expected: { 19 7 12 43 15 }\n\n");
  printf("Set size = %d, expected: 5\n\n", set.size);
  printf("43 is in idx: %d, expected: 3\n\n", exist_in_set(&set, 43));
  printf("Last elt:%d, expected: 15\n\n", pop_set(&set));
  print_set(&set);
  printf("Expected: { 19 7 12 43 }\n");
  printf("Set size = %d, expected: 4\n\n", set.size);
  delete_from_set(&set, 12);
  print_set(&set);
  printf("Expected: { 19 7 43 }\n");
  printf("Final set size: %d, expected: 3\n", set.size);
  delete_set(&set);
}

void test_movements()
{
  struct world_t *w = world_init();
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
  printf("\nPossible movements for piece 6: ");
  print_set(&set);
  printf("Expected: { 1 8 18 16 5 }\n");
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
  printf("\nPossible movements for piece 16: ");
  print_set(&set);
  printf("Expected: { 18 15 6 }\n");
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
  printf("\nPossible movements for piece 0: ");
  print_set(&set);
  printf("Expected: { 2 4 14 12 10 }\n");
  move_piece(w, 0, set.ptr[4]);
  print_world(w);
  delete_set(&set);
}

void test_game()
{
  struct world_t *w = world_init();
  init_game(w, 0);
  printf("The game is initialized: \n");
  print_world(w);
  printf("\n");
  print_set(&black_init_set);
  print_set(&black_current_set);
  printf("Expected: { 0 5 10 15 } (black pieces)\n\n");
  print_set(&white_init_set);
  print_set(&white_current_set);
  printf("Expected: { 4 9 14 19 } (white pieces)\n\n");
  print_set(&black_prison);
  printf("Expected: { }\n\n");

  printf("BLACK simple victory on place %d: %d, expected: 0\n", black_current_set.ptr[3], check_simple_victory(black_current_set.ptr[3], BLACK));

  move_piece(w, 4, 12);
  move_piece(w, 10, 4);

  print_world(w);

  printf("\n");
  print_set(&white_current_set);
  printf("Expected: { 12 9 14 19 } (white pieces)\n\n");
  print_set(&black_current_set);
  printf("Expected: { 0 5 4 15 } (black pieces)\n");

  srand(time(NULL));

  printf("\nRandom BLACK piece: %d\n", choose_random_piece_belonging_to(BLACK));
  printf("Random move for WHITE's 12th piece: %d\n\n", choose_random_move_for_piece(w, 12));

  printf("\nWHITE simple victory on place %d: %d, expected: 0\n", white_current_set.ptr[0], check_simple_victory(white_current_set.ptr[0], WHITE));
  printf("BLACK simple victory on place %d: %d, expected: 1\n", black_current_set.ptr[2], check_simple_victory(black_current_set.ptr[2], BLACK));
  printf("BLACK complex victory: %d, expected: 0\n\n", check_complex_victory(BLACK));

  print_set(&black_current_set);
  printf("Expected: { 0 5 15 } (black pieces)\n");

  move_piece(w, 9, 1);
  move_piece(w, 14, 10);
  move_piece(w, 19, 3);
  move_piece(w, 0, 19);
  move_piece(w, 5, 9);
  move_piece(w, 15, 14);

  print_world(w);

  printf("WHITE simple victory on place %d: %d, expected: 2\n", white_current_set.ptr[2], check_simple_victory(white_current_set.ptr[2], WHITE));
  printf("WHITE complex victory: %d, expected: 0\n\n", check_complex_victory(WHITE));

  print_set(&white_current_set);
  printf("Expected: { 12 1 3 } (white pieces)\n");

  printf("BLACK complex victory: %d, expected: 1\n", check_complex_victory(BLACK));

  print_set(&black_current_set);
  printf("Expected: { } (black pieces)\n");

  delete_set(&black_init_set);
  delete_set(&black_current_set);
  delete_set(&black_prison);
  delete_set(&white_init_set);
  delete_set(&white_current_set);
  delete_set(&white_prison);
}

void test_achiev1()
{
  struct world_t *w = world_init();
  world_set_sort(w, 15, 2);
  world_set(w, 15, 2);
  world_set_sort(w, 4, 2);
  world_set(w, 4, 1);
  world_set_sort(w, 1, 1);
  world_set(w, 1, 2);
  print_world(w);
  set_t set = possible_mvts(15, w);
  printf("\nPossible movements for tower 15: ");
  print_set(&set);
  printf("Expected: { 16 17 18 19 10 5 0 }\n");
  delete_set(&set);
  set = possible_mvts(4, w);
  printf("\nPossible movements for tower 4: ");
  print_set(&set);
  printf("Expected: { 9 14 19 3 2 }\n");
  delete_set(&set);

  world_set_sort(w, 12, 3);
  world_set(w, 12, 1);
  world_set_sort(w, 8, 1);
  world_set(w, 8, 2);
  set = possible_mvts(12, w);
  print_world(w);
  printf("\nPossible movements for elephant 12: ");
  print_set(&set);
  printf("Expected: { 2 6 10 16 18 14 }\n");
  delete_set(&set);
}

void test_achiev2()
{
  init_neighbors(2);
  printf("\nNeighbor of %d in direction %s: %d, expected: 16\n", 0, dir_to_string(2), get_neighbor(0, 2));
  printf("Neighbor of %d in direction %s: %d, expected: -1\n", 0, dir_to_string(4), get_neighbor(0, 4));
  printf("Neighbor of %d in direction %s: %d, expected: 18\n", 3, dir_to_string(3), get_neighbor(3, 3));
  printf("Neighbor of %d in direction %s: %d, expected: -1\n", 4, dir_to_string(2), get_neighbor(4, 2));
  printf("Neighbor of %d in direction %s: %d, expected: -1\n", 15, dir_to_string(-2), get_neighbor(15, -2));
  printf("Neighbor of %d in direction %s: %d, expected: -1\n", 10, dir_to_string(-2), get_neighbor(10, -2));
  printf("Neighbor of %d in direction %s: %d, expected: 2\n", 16, dir_to_string(-4), get_neighbor(16, -4));
  printf("\n");

  struct neighbors_t result = get_neighbors(9);
  printf("Neighbors of 9 in all directions: ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf(", expected: 14 13 8 4 3 -1 0 0 0\n");
  printf("\n");

  result = get_neighbors(17);
  printf("Neighbors of 17 in all directions: ");
  for (int p = 0; p < MAX_NEIGHBORS + 1; p++)
  {
    printf("%d ", result.n[p].i);
  }
  printf(", expected: 3 2 1 16 18 13 12 11 -1\n");
}

void test_achiev3()
{
  struct world_t *w = world_init();

  black_current_set = init_set(0);
  white_current_set = init_set(0);
  black_prison = init_set(0);
  white_prison = init_set(0);

  achiev3 = 1;

  world_set_sort(w, 11, 1);
  world_set(w, 11, 2);
  push_set(&white_current_set, 11);

  world_set_sort(w, 7, 1);
  world_set(w, 7, 1);
  push_set(&black_current_set, 7);

  print_world(w);

  printf("\nMove piece 11 to 7:\n");
  move_piece(w, 11, 7);
  print_world(w);

  printf("\nMove piece 7 to 8:\n");
  print_set(&black_prison);
  move_piece(w, 7, 8);
  print_world(w);

  printf("\nBLACK tries to make escape a piece:\n");
  escape(BLACK, w);
  print_world(w);
  printf("\n");
  print_set(&black_prison);

  delete_set(&black_current_set);
  delete_set(&white_current_set);
  delete_set(&black_prison);
  delete_set(&white_prison);
}

void test_achiev4()
{
  struct world_t *w = world_init();

  black_current_set = init_set(0);
  white_current_set = init_set(0);

  init_neighbors(0);

  world_set_sort(w, 12, 1);
  world_set(w, 12, 2);
  push_set(&white_current_set, 12);

  world_set_sort(w, 11, 1);
  world_set(w, 11, 1);
  push_set(&black_current_set, 11);

  print_world(w);

  set_t tmp_set = possible_mvts(12, w);
  printf("\nPossible movements for 12 with achiev 4 disactivated: ");
  print_set(&tmp_set);
  delete_set(&tmp_set);

  achiev4 = 1;
  tmp_set = possible_mvts(12, w);
  printf("Possible movements for 12 with achiev 4 activated: ");
  print_set(&tmp_set);
  delete_set(&tmp_set);

  achiev4 = 0;
  tmp_set = possible_mvts(11, w);
  printf("Possible movements for 11 with achiev 4 disactivated: ");
  print_set(&tmp_set);
  delete_set(&tmp_set);

  achiev4 = 1;
  printf("Possible movements for 11 with achiev4 activated: ");
  tmp_set = possible_mvts(11, w);
  print_set(&tmp_set);
  delete_set(&tmp_set);

  delete_set(&black_current_set);
  delete_set(&white_current_set);
}

int main()
{
  achiev3 = 0;
  achiev4 = 0;
  init_neighbors(0);

  printf("\n");
  printf("Geometry tests:\n");
  test_geometry();
  printf("\n\n");

  printf("World tests:\n");
  test_world();
  printf("\n\n");

  printf("Neighbors tests:\n");
  test_neighbors();
  printf("\n\n");

  printf("Set tests:\n");
  test_set();
  printf("\n\n");

  printf("Movements tests:\n");
  test_movements();
  printf("\n\n");

  printf("Game tests:\n");
  test_game();
  printf("\n\n");

  printf("Achiev1 tests:\n");
  test_achiev1();
  printf("\n\n");

  printf("Achiev2 tests:\n");
  test_achiev2();
  printf("\n\n");

  printf("Achiev3 tests:\n");
  test_achiev3();
  printf("\n\n");

  printf("Achiev4 tests:\n");
  test_achiev4();
  printf("\n\n");

  return 0;
}
