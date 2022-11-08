#include <stdio.h>
#include "world.h"

struct world_t{
  int c[WORLD_SIZE];
  int s[WORLD_SIZE];
};

struct world_t w;

struct * world_t world_init()
{
  for (int i = 0; i < WORLD_SIZE; i++)
    {
      w.c[i] = 0;
      w.s[i] = 0;
    }
return *w
}

int main ( int argc, char * argv[] )
{

  return 0; 
}
