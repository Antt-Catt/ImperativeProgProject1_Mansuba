#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"

const char* names_sort[] = {
  "NO_SORT","PAWN"
};

static const char* place_strings[MAX_SORT][MAX_COLOR] = {  
   {"NO_SORT NO_COLOR", "NO_SORT BLACK", "NO_SORT WHITE"} ,   
   {"PAWN NO_COLOR", "PAWN BLACK", "PAWN WHITE"} ,   
};

/** Return a string describing the color `c` and sort `s` */
const char* place_to_string(enum color_t c, enum sort_t s){
  return place_strings[s][c];
}

const char* names_dir[] = {
  "SEAST","SOUTH","SWEST","WEST","NO_DIR","EAST","NEAST","NORTH","NWEST"
};

/** Return a string describing the direction `d` */
const char* dir_to_string(enum dir_t d){
  return names_dir[d + 4];
}
