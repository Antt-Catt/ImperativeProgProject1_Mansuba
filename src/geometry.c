#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"

const char* names_color[] = {
  "NO_COLOR","BLACK","WHITE"
};

const char* names_sort[] = {
  "NO_SORT","PAWN"
};

//char result[32];

static const char* place_strings[MAX_SORT][MAX_COLOR];

const char* place_to_string(enum color_t c, enum sort_t s){
  // sprintf(result,"%s %s", names_color[c], names_sort[s]);
  static const char* result[MAX_SORT][MAX_COLOR] = {names_sort[c], names_color[s]} ;
  return result;
}

const char* names_dir[] = {
  "SEAST","SOUTH","SWEST","WEST","NO_DIR","EAST","NEAST","NORTH","NWEST"
};

const char* dir_to_string(enum dir_t d){
  return names_dir[d + 4];
}
