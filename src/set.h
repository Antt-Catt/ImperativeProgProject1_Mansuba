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

/** Initialize a set with size places */
set_t init_set(unsigned int size);

/** Resize the set's size with realloc */
void resize_set(set_t *set, int new_size);

/** Add an element at the end of the set */
void push_set(set_t *set, unsigned int x);

/** Remove the last element of the set and return it */
unsigned int pop_set(set_t *set);

/** Check if x exists in the set and return it's index */
unsigned int exist_in_set(set_t *set, unsigned int x);

/** Change the value of x in the set by y */
void modif_set(set_t *set, unsigned int x, unsigned int y);

/** Print the set */
void print_set(set_t *set);

/** Delete element x from the set*/
void delete_from_set(set_t *set, unsigned int x);

#endif // __SET_H__
