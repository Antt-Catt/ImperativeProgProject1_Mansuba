#ifndef __SET_H__
#define __SET_H__

#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"

typedef struct
{
    unsigned int *ptr;
    int size;
} set_t;

set_t init_set(unsigned int size);

unsigned int *get_set(set_t *set, unsigned int i);

void resize_set(set_t *set, int new_size);

void append_set(set_t *set, unsigned int x);

unsigned int pop_set(set_t *set);

unsigned int exist_set(set_t *set, unsigned int x);

void modif_set(set_t *set, unsigned int x, unsigned int y);

void print_set(set_t *set);

#endif // __SET_H__
