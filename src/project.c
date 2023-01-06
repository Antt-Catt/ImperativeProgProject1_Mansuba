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
  // for achiev3 and achiev4
  achiev3 = 0;
  achiev4 = 0;
  /*printf("Activer l'achievement 3 ? (0 pour non, autre sinon)\n");
  printf("%d\n", achiev3);
  scanf("%d", &achiev3);
  printf("%d\n", achiev3);*/

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

  init_game(w, 0); // first arg for world, second for seed, third for achiev3

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
      // tout sauf les tours ne depacent pas le milieu du terrain, mais ca marche lorsque achiev4 = 1 ??!
      // cest a cause du max turns = 9 hahah maintenant cest 100 ca marche, on doit penser apres ca a reduire la complexite peux etre?
      print_set(&black_current_set);
      print_set(&white_current_set);
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

  return 0;

  end_game();
}
