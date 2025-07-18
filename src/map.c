#include "map.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>

map_t GenerateMap(void)
{
    const int template[MAP_NUM_ROWS][MAP_NUM_COLS] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                      {1, 0, 2, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 3, 0, 2, 0, 1},
                                                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                      {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
                                                      {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
                                                      {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    map_t map = malloc(MAP_NUM_ROWS * MAP_NUM_COLS * sizeof(int *));
    for (int y = 0; y < MAP_NUM_ROWS; y++)
    {
        for (int x = 0; x < MAP_NUM_COLS; x++)
        {
            map[y * MAP_NUM_COLS + x] = template[y][x];
        }
    }
    return map;
}

int MapContentAtLocation(map_t map, Vector2 location)
{
    int x = floor(location.x / TILE_SIZE);
    int y = floor(location.y / TILE_SIZE);
    return map[y * MAP_NUM_COLS + x];
}

bool HasWallAtLocation(map_t map, Vector2 location)
{
    if (location.x < 0 || location.x > WINDOW_WIDTH || location.y < 0 || location.y > WINDOW_HEIGHT)
    {
        return true;
    }
    return MapContentAtLocation(map, location) != 0;
}
