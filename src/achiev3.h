#ifndef __ACHIEV3_H__
#define __ACHIEV3_H__

#include "world.h"
#include "game.h"
#include "set.h"

// imprisons a piece in place in world w, returns whether function succeeded
unsigned int imprison(unsigned int place, struct world_t *w);

// tries to make a piece of player escape its prison, returns whether function succeeded
unsigned int escape(unsigned int player, struct world_t *w);

#endif // __ACHIEV3_H__