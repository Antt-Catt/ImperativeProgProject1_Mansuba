#ifndef __ACHIEV1_H__
#define __ACHIEV1_H__

#include "game.h"
#include "world.h"
#include "set.h"
#include "achiev4.h"

extern unsigned int achiev4;

/** Returns possible movements for a tower piece */

set_t possible_mvts_tower(unsigned int idx, struct world_t *w);

/** Returns possible movements for an elephant piece */

set_t possible_mvts_elephant(unsigned int idx, struct world_t *w);

#endif // __ACHIEV1_H__
