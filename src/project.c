#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "project.h"

extern unsigned int achiev3;
extern unsigned int achiev4;

extern set_t black_init_set;
extern set_t black_current_set;
extern set_t black_prison;
extern set_t white_init_set;
extern set_t white_current_set;
extern set_t white_prison;

int main(int argc, char *argv[])
{
  // for achiev3 and achiev4
  achiev3 = 0;
  achiev4 = 1;
  // get optional values
  int opt;
  srand(time(NULL));
  int MAX_TURNS = 2 * WIDTH * HEIGHT;
  int victory_type = 0;
  while ((opt = getopt(argc, argv, "s:m:t:")) != -1)
  {
    switch (opt)
    {
    case 's':
      srand(atoi(optarg));
      break;
    case 'm':
      MAX_TURNS = atoi(optarg);
      break;
    case 't':
      if (strcmp(optarg, "c") == 0)
      {
        victory_type = 1;
      }
      break;
    }
  }

  int nb_turns = 0;
  struct world_t *w = world_init();

  init_neighbors(0);

  black_init_set = init_set(HEIGHT);
  white_init_set = init_set(HEIGHT);
  black_current_set = init_set(HEIGHT);
  white_current_set = init_set(HEIGHT);

  // for achiev3
  black_prison = init_set(0);
  white_prison = init_set(0);

  init_player_set(BLACK, w);
  init_player_set(WHITE, w);

  unsigned int current_player = (rand() % (2 - 1 + 1)) + 1;
  unsigned int p = choose_random_piece_belonging_to(current_player % 2 + 1);
  unsigned int m;

  print_world(w);

  if (victory_type == 0)
  {
    while ((check_simple_victory(p, current_player % 2 + 1) == 0) && (nb_turns != MAX_TURNS))
    {
      p = choose_random_piece_belonging_to(current_player);
      m = choose_random_move_for_piece(w, p);
      move_piece(w, p, m);
      current_player = current_player % 2 + 1;
      nb_turns++;
      p = m;
      print_world(w);
    }
    if (current_player == BLACK && nb_turns != MAX_TURNS)
    {
      printf("Victoire simple pour WHITE\n");
    }
    else if (current_player == WHITE && nb_turns != MAX_TURNS)
    {
      printf("Victoire simple pour BLACK\n");
    }
    else
    {
      printf("Pas de gagnant\n");
    }
  }

  if (victory_type == 1)
  {
    while ((check_complex_victory(current_player % 2 + 1) == 0) && (nb_turns != MAX_TURNS))
    {
      p = choose_random_piece_belonging_to(current_player);
      m = choose_random_move_for_piece(w, p);
      move_piece(w, p, m);
      current_player = current_player % 2 + 1;
      p = m;
      nb_turns++;
      print_world(w);
    }
  }

  print_world(w);

  delete_set(&black_current_set);
  delete_set(&white_current_set);
  delete_set(&black_init_set);
  delete_set(&white_init_set);
  delete_set(&black_prison);
  delete_set(&white_prison);

  return 0;
}
