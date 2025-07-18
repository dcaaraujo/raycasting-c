#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "map.h"
#include "raylib.h"

typedef struct player_t
{
    Vector2 location;
    Vector2 size;
    int turnDirection;
    int walkDirection;
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} player_t;

player_t *InitPlayer(void);
void ProcessInput(player_t *player);
void MovePlayer(player_t *player, map_t map);

#endif
