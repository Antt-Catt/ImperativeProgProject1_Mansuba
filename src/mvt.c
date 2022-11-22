#include <stdio.h>
#include <stdlib.h>
#include "neighbors.h"
#include "world.h"
#include "set.h"

extern struct world_t w;

set_t fct_mvt_1(unsigned int idx)
{
    set_t set = init_set(0);
    struct neighbors_t neigh_idx = get_neighbors(idx);
    for (int j = 0; j < MAX_NEIGHBORS + 1; j++)
    {
        unsigned int idx_n = neigh_idx.n[j].i;
        if (w.s[idx_n] == 0)
        {
            append_set(&set, idx_n);
        }
    }
    return set;
}

set_t mvt = init_set(0);

set_t fct_mvt_2(unsigned int idx, set_t *set)
{
    struct neighbors_t neigh_idx = get_neighbors(idx);
    for (int j = 0; j < MAX_NEIGHBORS + 1; j++)
    {
        unsigned int idx_n = neigh_idx.n[j].i;
        if (w.s[idx_n] != 0)
        {
            idx_n;
        }
    }
}

int main()
{

    return 0;
}