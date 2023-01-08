#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "project.h"

int main(int argc, char *argv[])
{
  achiev3 = 1;
  achiev4 = 1;

  int opt;
  srand(time(NULL));
  unsigned int MAX_TURNS = 2 * WIDTH * HEIGHT;
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

  struct world_t *w = world_init();
  init_game(w, 0);

  current_player = (rand() % (2 - 1 + 1)) + 1;
  unsigned int p = choose_random_piece_belonging_to(current_player % 2 + 1);
  unsigned int m;

  printf("░░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░░\n");
  print_world(w);

  if (victory_type == 0)
  {
    while ((check_simple_victory(p, current_player % 2 + 1) == 0) && (nb_turns != MAX_TURNS))
    {
      nb_turns++;
      p = choose_random_piece_belonging_to(current_player);
      m = choose_random_move_for_piece(w, p);
      move_piece(w, p, m);
      print_world(w);
      current_player = current_player % 2 + 1;
      p = m;
    }
    if (current_player == BLACK && nb_turns != MAX_TURNS)
    {
      printf("░░▒▒░░▒▒▒░  GAME OVER  ░▒▒▒░░▒▒░░\n");
      printf("░░ WHITE WON  (SIMPLE VICTORY) ░░\n");
      printf("░░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░░\n\n");
    }
    else if (current_player == WHITE && nb_turns != MAX_TURNS)
    {
      printf("░░▒▒░░▒▒▒░  GAME OVER  ░▒▒▒░░▒▒░░\n");
      printf("░░ BLACK WON  (SIMPLE VICTORY) ░░\n");
      printf("░░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░░\n\n");
    }
    else
    {
      printf("░░▒▒░░▒▒░   GAME OVER   ░▒▒░░▒▒░░\n");
      printf("░░▒▒░░▒▒░  NO ONE  WON  ░▒▒░░▒▒░░\n");
      printf("░░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░░\n\n");
    }
  }

  if (victory_type == 1)
  {
    while ((check_complex_victory(current_player % 2 + 1) == 0) && (nb_turns != MAX_TURNS))
    {
      nb_turns++;
      p = choose_random_piece_belonging_to(current_player);
      m = choose_random_move_for_piece(w, p);
      move_piece(w, p, m);
      print_world(w);
      current_player = current_player % 2 + 1;
      p = m;
    }
    if (nb_turns == MAX_TURNS)
    {
      printf("\n\nGAME OVER: NO ONE WON!\n\n");
    }
  }

  end_game();

  return 0;
}
