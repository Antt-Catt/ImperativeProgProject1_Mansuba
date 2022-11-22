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

/** Initializes a set (0 element)
    Always return the same set*/
set_t init_set(unsigned int size);

/** Resize the set's size with realloc */
void resize_set(set_t *set, int new_size);

<<<<<<< HEAD
void push_set(set_t *set, unsigned int x);
=======
/** Add an element at the end of the set */
void append_set(set_t *set, unsigned int x);
>>>>>>> a1a1c1523d7a983e509580aa48fca62a71365e24

/** Remove the last element and return it */
unsigned int pop_set(set_t *set);

<<<<<<< HEAD
unsigned int exist_in_set(set_t *set, unsigned int x);
=======
/** Check if an element exists in the set and return his index */
unsigned int exist_set(set_t *set, unsigned int x);
>>>>>>> a1a1c1523d7a983e509580aa48fca62a71365e24

/** Change the value of an element in the set */
void modif_set(set_t *set, unsigned int x, unsigned int y);

/** Print the set */
void print_set(set_t *set);

#endif // __SET_H__
