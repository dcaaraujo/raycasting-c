#ifndef _RAY_H_
#define _RAY_H_

#include "player.h"
#include "raylib.h"
#include "raymath.h"

typedef struct ray_t
{
    float angle;
    float distance;
    Vector2 wallHitLocation;
    bool wasHitVertical;
    int wallContent;
} ray_t;

void CastRays(player_t *player, map_t map, ray_t *rays);

#endif
