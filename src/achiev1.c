#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include "achiev1.h"

set_t possible_mvts_tower(unsigned int idx, struct world_t *w)
{
    set_t set = init_set(0);
    int j = -3;
    while (j < 4)
    {
        unsigned int idx_n = get_neighbor(idx, j);
        if (world_get_sort(w, idx_n) == 0)
        {
            push_set(&set, idx_n);
        }
        while (idx_n != UINT_MAX)
        {
            idx_n = get_neighbor(idx_n, j);
            if (world_get_sort(w, idx_n) == 0)
            {
                push_set(&set, idx_n);
            }
        }
        j += 2;
    }
    return set;
}

set_t possible_mvts_elephant(unsigned int idx, struct world_t *w)
{
    set_t set = init_set(0);
    int j;
    unsigned int idx_n;
    j = -3;
    while (j < 4)
    {
        idx_n = get_neighbor(get_neighbor(idx, j), j);
        if (idx_n != UINT_MAX && world_get_sort(w, idx_n) == 0)
        {
            push_set(&set, idx_n);
        }
        j += 2;
    }

    j = -4;
    while (j < 5)
    {
        idx_n = get_neighbor(idx, j);
        if (idx_n != UINT_MAX && world_get_sort(w, idx_n) == 0)
        {
            push_set(&set, idx_n);
        }
        j += 2;
        if (j == 0)
        {
            j += 2;
        }
    }
    print_set(&set);
    return set;
}