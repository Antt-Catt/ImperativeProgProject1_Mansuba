#include <stdio.h>
#include "world.h"
#include "set.h"
#include "geometry.h"

/** Abstract struct representing the possible places in the world
    These places are indexed from 0 to WORLD_SIZE-1 */

struct world_t
{
  int c[WORLD_SIZE];
  int s[WORLD_SIZE];
};

struct world_t w;

/** Initializes a world (NO_COLOR, NO_SORT everywhere)
    Always returns the same pointer */
struct world_t * world_init()
{
  for (int i = 0; i < WORLD_SIZE; i++)
  {
    w.c[i] = 0;
    w.s[i] = 0;
  }
  return &w;
}

/** Return the color at a place */
enum color_t world_get(const struct world_t *b, unsigned int idx)
{
  return (*b).c[idx];
}

/** Sets the color at a place */
void world_set(struct world_t *b, unsigned int idx, enum color_t c)
{
  (*b).c[idx] = c;
}

/** Return the sort at a place */
enum sort_t world_get_sort(const struct world_t *b, unsigned int idx)
{
  return (*b).s[idx];
}

/** Sets the sort at a place */
void world_set_sort(struct world_t *b, unsigned int idx, enum sort_t c)
{
  (*b).s[idx] = c;
<<<<<<< HEAD
}

set_t black_init_set;
set_t black_current_set;

set_t white_init_set;
set_t white_current_set;

void init_player_set(unsigned int p)
{
  for (int i = 0; i < HEIGHT; i++)
  {
    w.c[WIDTH * i] = p;
    w.c[WIDTH * i] = PAWN;
    if (p == BLACK)
    {
      push_set(&black_init_set, WIDTH * i);
    }
    else
    {
      push_set(&white_init_set, WIDTH * i);
    }
  }
}

void check_simple_victory(unsigned int idx, unsigned int p)
{
  for (int i = 0; i < HEIGHT; i++)
  {
    if (p == 1)
    {
      if (idx == black_init_set.ptr[i])
      {
        printf("Victoire simple pour WHITE");
      }
    }
    else
    {
      if (idx == white_init_set.ptr[i])
      {
        printf("Victoire simple pour BLACK");
      }
    }
  }
=======
>>>>>>> a1a1c1523d7a983e509580aa48fca62a71365e24
}