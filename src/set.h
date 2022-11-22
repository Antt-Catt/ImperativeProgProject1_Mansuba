#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"

typedef struct
{
    unsigned int *ptr;
    int size;
} set_t;

set_t init_set(int size);

unsigned int *get_set(set_t *set, unsigned int i);

void resize_set(set_t *set, int new_size);

void append_set(set_t *set, unsigned int x);

unsigned int pop_set(set_t *set);

unsigned int exist_set(set_t *set, unsigned int x);

void modif_set(set_t *set, unsigned int x, unsigned int y);

#endif // __ENSEMBLE_H__
