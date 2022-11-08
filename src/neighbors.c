#include <stdio.h>
#include <stdlib.h>
#include "neighbors.h"

void init_neighbors(unsigned int seed){
}

unsigned int get_neighbor(unsigned int idx, enum dir_t d){
  int i = idx / WIDTH;
  int j = idx % WIDTH;
  if (i == 0 && (d == 2 || d == 3 || d == 4)){
    return UINT_MAX;
  }
  if (j == 0 && (d == -1 || d == -2 || d == 4)){
    return UINT_MAX;
  }
  if (i == (HEIGHT - 1) && (d == -2 || d == -3 || d == -4)){
    return UINT_MAX;
  }
  if (j == (WIDTH - 1) && (d == 1 || d == 2 || d == -4)){
    return UINT_MAX;
  }
  switch{
  case -4:
    return idx + WIDTH + 1;
  case -3:
    return idx + WIDTH;
  case -2:
    return idx + WIDTH - 1;
  case -1:
    return idx - 1 ;
  case 0:
    return UINT_MAX;
  case 1:
    return idx + 1;
  case 2:
    return idx - WIDTH + 1;
  case 3:
    return idx - WIDTH;
  case 4:
    return idx - WIDTH - 1;
  }
}

int main(int argc, char* argv[]){
  return 0;
}
