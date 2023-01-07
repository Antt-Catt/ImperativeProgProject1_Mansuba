#ifndef __ACHIEV3_H__
#define __ACHIEV3_H__

#include "movements.h"

extern unsigned int achiev3;
extern set_t black_prison;
extern set_t white_prison;

// Imprisons a piece in place in world w, returns whether function succeeded
unsigned int imprison(unsigned int place, struct world_t *w);

// Tries to make a piece of player escape its prison, returns whether function succeeded
unsigned int escape(unsigned int player, struct world_t *w);

#endif // __ACHIEV3_H__
