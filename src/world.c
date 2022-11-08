#include <stdio.h>
#include "world.h"

struct world_t{
  int c[WORLD_SIZE];
  int s[WORLD_SIZE];
};

struct world_t w;

struct world_t * world_init()
{
  for (int i = 0; i < WORLD_SIZE; i++)
    {
      w.c[i] = 0;
      w.s[i] = 0;
    }
  return &w;
}

enum color_t world_get(const struct world_t* b, unsigned int idx)
{
  return (*b).c[idx];
}

void world_set(struct world_t* b, unsigned int idx, enum color_t c)
{
  (*b).c[idx] = c;
}

enum sort_t world_get_sort(const struct world_t* b, unsigned int idx)
{
  return (*b).s[idx];
}

void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c)
{
  (*b).s[idx] = c;
}


int main ( int argc, char * argv[] )
{
  return 0; 
}
