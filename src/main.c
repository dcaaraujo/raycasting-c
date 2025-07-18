#include "constants.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "render.h"
#include <stdlib.h>

int main(void)
{
    map_t map = GenerateMap();
    player_t *player = InitPlayer();
    ray_t rays[RAY_COUNT];
    colorbuffer_t colorBuffer = InitColorBuffer();

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raycaster");
    SetTargetFPS(FRAMERATE);
    while (!WindowShouldClose())
    {
        ProcessInput(player);
        MovePlayer(player, map);
        CastRays(player, map, rays);
        RenderScreen(player, map, rays, colorBuffer);
    }
    CloseWindow();

    free(player);
    free(map);
    free(colorBuffer);

    return EXIT_SUCCESS;
}
