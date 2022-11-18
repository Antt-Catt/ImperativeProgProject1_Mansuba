#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"


typedef struct{
unsigned int * ptr;
 int size;
} set_t;

set_t init_set (int size);

set_t resize_set (set_t ens, int new_size);


#endif // __ENSEMBLE_H__
