#ifndef _RENDER_H_
#define _RENDER_H_

#include "player.h"
#include "ray.h"
#include "raylib.h"

typedef Color *colorbuffer_t;

colorbuffer_t InitColorBuffer(void);
void RenderScreen(player_t *player, map_t map, ray_t *rays, Color *colorBuffer);

#endif
