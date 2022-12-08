#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include "project.h"
#include "movements.h"
#include "neighbors.h"
#include "set.h"

set_t possible_mvts_tower(unsigned int idx, struct world_t *w)
{
    set_t set = init_set(0);
    int j = -3;
    while (j < 4)
    {
        unsigned int idx_n = get_neighbor(idx, j);
        while (idx_n != UINT_MAX)
        {
            push_set(&set, idx_n);
            idx_n = get_neighbor(idx_n, j);
        }
        j += 2;
    }
    return set;
}