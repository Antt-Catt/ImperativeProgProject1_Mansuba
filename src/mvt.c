#include <stdio.h>
#include <stdlib.h>
#include "neighbors.h"
#include "world.h"
#include "set.h"

extern struct world_t w;

void mvt_possibles_aux(set_t *set, unsigned int idx)
{
    struct neighbors_t neigh_idx = get_neighbors(idx);
    unsigned int idx_n;
    for (int j = 0; j < MAX_NEIGHBORS + 1; j++)
    {
        idx_n = neigh_idx.n[j].i;
        if (world_get_sort(&w, idx_n) != 0)
        {
            idx_n = get_neighbor(idx_n, neigh_idx.n[j].d);
            if (world_get_sort(&w, idx_n) == 0)
            {
                push_set(set, idx_n);
                mvt_possibles_aux(set, idx_n);
            }
        }
    }
}

set_t mvt_possibles(unsigned int idx)
{
    set_t set = init_set(0);
    struct neighbors_t neigh_idx = get_neighbors(idx);
    for (int j = 0; j < MAX_NEIGHBORS; j++)
    {
        unsigned int idx_n = neigh_idx.n[j].i;
        if (world_get_sort(&w, idx_n) == 0)
        {
            push_set(&set, idx_n);
        }
        else
        {
            idx_n = get_neighbor(idx_n, neigh_idx.n[j].d);
            if (world_get_sort(&w, idx_n) == 0)
            {
                push_set(&set, idx_n);
                mvt_possibles_aux(&set, idx_n);
            }
        }
    }
    return set;
}

int main()
{
    set_t set = mvt_possibles(8);
    print_set(&set);
    return 0;
}