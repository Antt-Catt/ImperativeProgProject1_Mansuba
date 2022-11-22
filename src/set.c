#include "set.h"
#include <limits.h>

set_t init_set(unsigned int size)
{
  set_t set;
  set.ptr = malloc(size * sizeof(unsigned int));
  set.size = size;
  return set;
};

void resize_set(set_t *set, int new_size)
{
  (*set).ptr = realloc((*set).ptr, new_size * sizeof(unsigned int));
  (*set).size = new_size;
};

void append_set(set_t *set, unsigned int x)
{
  resize_set(set, ((*set).size + 1));
  (*set).ptr[(*set).size - 1] = x;
};

unsigned int pop_set(set_t *set)
{
  int x = (*set).ptr[(*set).size - 1];
  resize_set(set, ((*set).size - 1));
  return x;
};

unsigned int exist_set(set_t *set, unsigned int x)
{
  for (int i = 0; i < (*set).size; i++)
  {
    if ((*set).ptr[i] == x)
    {
      return i;
    }
  }
  return UINT_MAX;
};

void modif_set(set_t *set, unsigned int x, unsigned int y)
{
  unsigned int i = exist_set(set, x);
  if (i != UINT_MAX)
  {
    (*set).ptr[i] = y;
  }
}

void print_set(set_t *set)
{
  for (int i = 0; i < (*set).size; i++)
  {
    printf("%d", (*set).ptr[i]);
    if (i % WIDTH == 0)
    {
      printf("\n")
    }
  }
  printf("\n")
}

int main()
{

  set_t ens = init_set(5);
  append_set(&ens, 17);
  int w = ens.size;
  modif_set(&ens, 17, 19);
  int y = pop_set(&ens);
  int z = ens.size;
  printf("%d, %d, %d\n", w, y, z);

  return 0;
}
