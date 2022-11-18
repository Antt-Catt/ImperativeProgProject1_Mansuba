#include "set.h"

set_t init_set(int size){
  set_t set;
  set.ptr = malloc(size * sizeof(unsigned int));
  set.size = size;
  return set;
};

set_t resize_set(set_t set, int new_size){
  set.ptr = realloc(set.ptr, new_size * sizeof(unsigned int));
  set.size = new_size;
  return set;
};

set_t append(set_t set, unsigned int x){
  set = resize_set(set, (set.size + 1));
  *(set.ptr + set.size) = x;
};

int main(){
  set_t ens = init_set(5);
  if ( ens.ptr != NULL) {
    *ens.ptr = 12;
    *(ens.ptr +50) = 17;
  }

  return 0;
}
