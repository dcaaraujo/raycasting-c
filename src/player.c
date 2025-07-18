#include "player.h"
#include "constants.h"

#include <math.h>
#include <stdlib.h>

player_t *InitPlayer(void)
{
    player_t *player = malloc(sizeof(player_t));
    player->location = (Vector2){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    player->size = (Vector2){1, 1};
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->rotationAngle = PI / 2;
    player->walkSpeed = 100;
    player->turnSpeed = (PI / 180) * 45;
    return player;
}

void ProcessInput(player_t *player)
{
    if (IsKeyDown(KEY_UP))
    {
        player->walkDirection = +1;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        player->walkDirection = -1;
    }
    else
    {
        player->walkDirection = 0;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        player->turnDirection = -1;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        player->turnDirection = +1;
    }
    else
    {
        player->turnDirection = 0;
    }
}

void MovePlayer(player_t *player, map_t map)
{
    player->rotationAngle += player->turnDirection * player->turnSpeed * GetFrameTime();

    float moveStep = player->walkDirection * player->walkSpeed * GetFrameTime();
    Vector2 newLocation = player->location;
    newLocation.x += cos(player->rotationAngle) * moveStep;
    newLocation.y += sin(player->rotationAngle) * moveStep;

    if (!HasWallAtLocation(map, newLocation))
    {
        player->location = newLocation;
    }
}
