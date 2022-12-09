#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "set.h"

set_t init_set(unsigned int size)
{
  set_t set;
  set.ptr = malloc(size * sizeof(unsigned int));
  set.size = size;
  return set;
}

void resize_set(set_t *set, int new_size)
{
  (*set).ptr = realloc((*set).ptr, new_size * sizeof(unsigned int));
  (*set).size = new_size;
}

void push_set(set_t *set, unsigned int x)
{
  resize_set(set, ((*set).size + 1));
  (*set).ptr[(*set).size - 1] = x;
}

unsigned int pop_set(set_t *set)
{
  int x = (*set).ptr[(*set).size - 1];
  resize_set(set, ((*set).size - 1));
  return x;
}

unsigned int exist_in_set(set_t *set, unsigned int x)
{
  for (int i = 0; i < (*set).size; i++)
  {
    if ((*set).ptr[i] == x)
    {
      return i;
    }
  }
  return UINT_MAX;
}

void modif_set(set_t *set, unsigned int x, unsigned int y)
{
  unsigned int i = exist_in_set(set, x);
  if (i != UINT_MAX)
  {
    (*set).ptr[i] = y;
  }
}

void print_set(set_t *set)
{
  printf("{ ");
  for (int i = 0; i < (*set).size; i++)
  {
    printf("%d ", (*set).ptr[i]);
  }
  printf("}\n");
}

void delete_from_set(set_t *set, unsigned int x)
{
  int y = (*set).ptr[(*set).size - 1];
  modif_set(set, x, y);
  pop_set(set);
}

void delete_set(set_t *set)
{
  (*set).size = 0;
  free((*set).ptr);
}
