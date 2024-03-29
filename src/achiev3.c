// some includes should be removed
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "achiev3.h"

unsigned int achiev3;

set_t black_prison;
set_t white_prison;

// Imprisons a piece in place in world w, returns whether function succeeded
unsigned int imprison(unsigned int idx, struct world_t *w)
{

  if (exist_in_set(&black_init_set, idx) == UINT_MAX && exist_in_set(&white_init_set, idx) == UINT_MAX) // if place not in initial positions
    {
        unsigned int player = world_get(w, idx);
        unsigned int sort = world_get_sort(w, idx);
        world_set(w, idx, 0);
        world_set_sort(w, idx, 0);
        if (player == BLACK)
        {
            push_set(&black_prison, idx);
            push_set(&black_prison, sort);
            delete_from_set(&black_current_set, idx);
        }
        else if (player == WHITE)
        {
            push_set(&white_prison, idx);
            push_set(&white_prison, sort);
            delete_from_set(&white_current_set, idx);
        }
        return 0;
    }
    return UINT_MAX;
}

// Tries to make a piece of player escape its prison, returns whether function succeeded
unsigned int escape(unsigned int player, struct world_t *w)
{
    int i;
    unsigned int idx;
    unsigned int tmp;
    unsigned int tmp_t;
    unsigned int sort;

    if (player == BLACK)
    {
        if (black_prison.size < 2)
        {
            return UINT_MAX;
        }
        tmp_t = (black_prison.size / 2) - 1;
        i = (rand() % (tmp_t + 1)); // choose random piece in prison
        idx = black_prison.ptr[2 * i];
        sort = black_prison.ptr[2 * i + 1];
        tmp = world_get(w, idx);
        if (tmp != 0)
        {
            return UINT_MAX;
        }
        tmp = (rand() % 2) + 1; // to have 50% of chance of escape
        if (tmp != 2)
        {
            return 1;
        }
	// here escape is successfull
        world_set(w, idx, player);
        world_set_sort(w, idx, sort);
        black_prison.ptr[2 * i] = black_prison.ptr[black_prison.size - 2];
        black_prison.ptr[2 * i + 1] = black_prison.ptr[black_prison.size - 1];
        pop_set(&black_prison);
        push_set(&black_current_set, pop_set(&black_prison));
        return 0;
    }
    else if (player == WHITE)
    {
        if (white_prison.size < 2)
        {
            return UINT_MAX;
        }
        tmp_t = (white_prison.size / 2) - 1;
        i = (rand() % (tmp_t + 1)); // choose random piece in prison
        idx = white_prison.ptr[2 * i];
        sort = white_prison.ptr[2 * i + 1];
        tmp = world_get(w, idx);
        if (tmp != 0)
        {
            return UINT_MAX;
        }
        tmp = (rand() % 2) + 1; // to have 50% of chance of escape
        if (tmp != 2)
        {
            return 1;
        }
	// here escape is successfull
        world_set(w, idx, player);
        world_set_sort(w, idx, sort);
        white_prison.ptr[2 * i] = white_prison.ptr[white_prison.size - 2];
        white_prison.ptr[2 * i + 1] = white_prison.ptr[white_prison.size - 1];
        pop_set(&white_prison);
        push_set(&white_current_set, pop_set(&white_prison));
        return 0;
    }
    return UINT_MAX;
}
