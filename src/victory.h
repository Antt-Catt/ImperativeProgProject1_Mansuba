#ifndef __VICTORY_H__
#define __VICTORY_H__

#include "movements.h"

/** Checks simple victory for piece at index idx of player p */
int check_simple_victory(unsigned int idx, unsigned int p);

/** Checks complex victory for player p */
int check_complex_victory(unsigned int p);

#endif // __VICTORY_H__

