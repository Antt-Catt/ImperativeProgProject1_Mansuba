#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "neighbors.h"
#include "world.h"
#include "set.h"

struct world_t
{
    int c[WORLD_SIZE];
    int s[WORLD_SIZE];
};

void mvt_possibles_aux(set_t *set, unsigned int idx, struct world_t *w, unsigned int init)
{
    int j = 0;
    unsigned int idx_n;
    struct neighbors_t neigh_idx = get_neighbors(idx);
    if (exist_in_set(set, idx) == UINT_MAX && idx != init)
    {
        push_set(set, idx);
    }
    while (neigh_idx.n[j].i != UINT_MAX)
    {
        idx_n = neigh_idx.n[j].i;
        if (world_get_sort(w, idx_n) != 0)
        {
            idx_n = get_neighbor(idx_n, neigh_idx.n[j].d);
            if (world_get_sort(w, idx_n) == 0)
            {
                if (exist_in_set(set, idx_n) == UINT_MAX && idx_n != init)
                {
                    mvt_possibles_aux(set, idx_n, w, init);
                }
            }
        }
        j++;
    }
}

set_t mvt_possibles(unsigned int idx, struct world_t *w)
{
    set_t set = init_set(0);
    struct neighbors_t neigh_idx = get_neighbors(idx);
    int j = 0;
    while (neigh_idx.n[j].i != UINT_MAX)
    {
        unsigned int idx_n = neigh_idx.n[j].i;
        if (world_get_sort(w, idx_n) == 0)
        {
            push_set(&set, idx_n);
        }
        else
        {
            idx_n = get_neighbor(idx_n, neigh_idx.n[j].d);
            if (world_get_sort(w, idx_n) == 0)
            {
                mvt_possibles_aux(&set, idx_n, w, idx);
            }
        }
        j++;
    }
    return set;
}

int main()
{

    struct world_t w;
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        w.c[i] = 0;
        w.s[i] = 0;
    }
    set_t set;
    world_set_sort(&w, 1, 1);
    world_set_sort(&w, 3, 1);
    world_set_sort(&w, 13, 1);
    world_set_sort(&w, 30, 1);
    world_set_sort(&w, 31, 1);
    set = mvt_possibles(0, &w);
    print_set(&set);
    return 0;
}