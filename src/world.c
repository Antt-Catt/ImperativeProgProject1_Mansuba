#include <stdio.h>
#include <limits.h>

#include "world.h"

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
struct world_t *world_init()
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
  if (idx == UINT_MAX)
  {
    return MAX_COLOR;
  }
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
  if (idx == UINT_MAX)
  {
    return MAX_SORT;
  }
  return (*b).s[idx];
}

/** Sets the sort at a place */
void world_set_sort(struct world_t *b, unsigned int idx, enum sort_t c)
{
  (*b).s[idx] = c;
}
