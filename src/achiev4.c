#include <stdio.h>
#include <stdlib.h>

#include "achiev4.h"

/** Optimises a set of possible movements */
set_t achiev4_mvts(set_t *set, unsigned int player)
{
  unsigned int tmp;
  set_t result = init_set(0);
  if (player == BLACK)
  {
    tmp = 0;
    for (int i = 0; i < (*set).size; i++) // get the nearest position to victory
    {
      if ((*set).ptr[i] % WIDTH > tmp) // > because white position are 
      {
        tmp = (*set).ptr[i] % WIDTH;
      }
    }
    for (int i = 0; i < (*set).size; i++)
    {
      if ((*set).ptr[i] % WIDTH == tmp)
      {
        push_set(&result, (*set).ptr[i]);
      }
    }
  }
  else if (player == WHITE)
  {
    tmp = WIDTH;
    for (int i = 0; i < (*set).size; i++) // get the nearest position to victory
    {
      if ((*set).ptr[i] % WIDTH < tmp)
      {
        tmp = (*set).ptr[i] % WIDTH;
      }
    }
    for (int i = 0; i < (*set).size; i++)
    {
      if ((*set).ptr[i] % WIDTH == tmp)
      {
        push_set(&result, (*set).ptr[i]);
      }
    }
  }
  delete_set(set);
  return result;
}
