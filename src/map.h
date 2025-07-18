#ifndef _MAP_H_
#define _MAP_H_

#include "raylib.h"

#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20

typedef int *map_t;

map_t GenerateMap(void);
int MapContentAtLocation(map_t map, Vector2 location);
bool HasWallAtLocation(map_t map, Vector2 location);

#endif
