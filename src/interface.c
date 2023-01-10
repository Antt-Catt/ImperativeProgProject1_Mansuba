#include <stdio.h>
#include <stdlib.h>

#include "interface.h"

unsigned int nb_turns;

/** Shows world w*/
void print_world(struct world_t *w)
{
    if (nb_turns == 0)
    {
        printf("\n▒░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░▒\n");
        printf("▒░▒▒░░▒▒▒░ GAME BEGINS ░▒▒▒░░▒▒░▒\n");
        printf("▒░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░▒\n\n");
    }
    else if (nb_turns < 10)
    {
        printf("▒░▒▒░░▒▒▒░░ TURN:  0%d ░░▒▒▒░░▒▒░▒\n", nb_turns);
    }
    else
    {
        printf("▒░▒▒░░▒▒▒░░ TURN:  %d ░░▒▒▒░░▒▒░▒\n", nb_turns);
    }
    if (current_player == BLACK && nb_turns!= 0)
    {
        printf("▒░▒▒░░▒▒▒ PLAYER: BLACK ▒▒▒░░▒▒░▒\n");
    }
    else if (nb_turns != 0)
    {
        printf("▒░▒▒░░▒▒▒ PLAYER: WHITE ▒▒▒░░▒▒░▒\n");
    }

    if (nb_turns != 0)
    {
        printf("▒░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░▒\n\n");
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        if (get_neighbors_seed() == 1 && i % 2 == 1)
        {
            printf("\t");
        }

        for (int j = 0; j < WIDTH; j++)
        {
            if (world_get_sort(w, i * WIDTH + j) == NO_SORT && world_get(w, i * WIDTH + j) == NO_COLOR)
            {
                printf("·\t");
            }
            else if (world_get(w, i * WIDTH + j) == BLACK)
            {
                switch (world_get_sort(w, j + i * WIDTH))
                {
                case 1:
                    printf("♟\t");
                    break;
                case 2:
                    printf("♜\t");
                    break;
                case 3:
                    printf("♝\t");
                    break;
                default:
                    break;
                }
            }
            else if (world_get(w, i * WIDTH + j) == WHITE)
            {
                switch (world_get_sort(w, j + i * WIDTH))
                {
                case 1:
                    printf("♙\t");
                    break;
                case 2:
                    printf("♖\t");
                    break;
                case 3:
                    printf("♗\t");
                    break;
                default:
                    break;
                }
            }
            else
            {
                printf("?\t\t");
            }
        }
        printf("\n\n");
    }
    printf("▒░▒▒░░▒▒▒░░░▒▒▒▒▒▒▒▒▒░░░▒▒▒░░▒▒░▒\n");
}