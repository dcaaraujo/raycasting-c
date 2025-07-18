#include "render.h"
#include "constants.h"
#include "map.h"
#include <stdlib.h>

void ClearColorBuffer(colorbuffer_t colorBuffer)
{
    for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++)
    {
        colorBuffer[i] = BLUE;
    }
}

void Generate3DProjection(player_t *player, ray_t *rays, colorbuffer_t colorBuffer)
{
    for (int i = 0; i < RAY_COUNT; i++)
    {
        ray_t ray = rays[i];
        float perpDistance = ray.distance * cos(ray.angle - player->rotationAngle);
        float projectedWallHeight = (TILE_SIZE / perpDistance) * DISTANCE_TO_PROJECTION_PLANE;

        int wallStripHeight = (int)projectedWallHeight;
        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

        for (int y = 0; y < wallTopPixel; y++)
        {
            colorBuffer[(WINDOW_WIDTH * y) + i] = (Color){100, 100, 100, 255};
        }

        for (int y = wallTopPixel; y < wallBottomPixel; y++)
        {
            Color pixelColor;
            switch (ray.wallContent)
            {
            case 2:
                pixelColor = ray.wasHitVertical ? RED : (Color){200, 0, 0, 255};
                break;
            case 3:
                pixelColor = ray.wasHitVertical ? GREEN : (Color){0, 200, 0, 255};
                break;
            case 4:
                pixelColor = ray.wasHitVertical ? BLUE : (Color){0, 0, 200, 255};
                break;
            default:
                pixelColor = ray.wasHitVertical ? WHITE : (Color){240, 240, 240, 255};
            }

            colorBuffer[(WINDOW_WIDTH * y) + i] = pixelColor;
        }

        for (int y = wallBottomPixel; y < WINDOW_HEIGHT; y++)
        {
            colorBuffer[(WINDOW_WIDTH * y) + i] = LIGHTGRAY;
        }
    }
}

void RenderMap(map_t map)
{
    for (int i = 0; i < MAP_NUM_ROWS; i++)
    {
        for (int j = 0; j < MAP_NUM_COLS; j++)
        {
            Vector2 tileLocation = {j * TILE_SIZE, i * TILE_SIZE};
            Vector2 tileSize = {TILE_SIZE, TILE_SIZE};
            Color tileColor = MapContentAtLocation(map, tileLocation) == 0 ? BLACK : WHITE;
            DrawRectangleV(Vector2Scale(tileLocation, MINIMAP_SCALE_FACTOR),
                           Vector2Scale(tileSize, MINIMAP_SCALE_FACTOR), tileColor);
        }
    }
}

void RenderPlayer(player_t *player)
{
    Vector2 playerLocation = Vector2Scale(player->location, MINIMAP_SCALE_FACTOR);
    Vector2 playerSize = Vector2Scale(player->size, MINIMAP_SCALE_FACTOR);
    DrawRectangleV(playerLocation, playerSize, WHITE);
}

void RenderRays(player_t *player, ray_t *rays)
{
    Vector2 playerLocation = Vector2Scale(player->location, MINIMAP_SCALE_FACTOR);

    for (int i = 0; i < RAY_COUNT; i++)
    {
        Vector2 collisionLocation = Vector2Scale(rays[i].wallHitLocation, MINIMAP_SCALE_FACTOR);
        DrawLineV(playerLocation, collisionLocation, YELLOW);
    }
}

colorbuffer_t InitColorBuffer(void)
{
    return malloc(sizeof(Color) * WINDOW_WIDTH * WINDOW_HEIGHT);
}

void RenderScreen(player_t *player, map_t map, ray_t *rays, colorbuffer_t colorBuffer)
{
    BeginDrawing();
    ClearBackground(BLACK);
    Generate3DProjection(player, rays, colorBuffer);
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        for (int y = 0; y < WINDOW_HEIGHT; y++)
        {
            Color pixelColor = colorBuffer[(WINDOW_WIDTH * y) + x];
            DrawPixel(x, y, pixelColor);
        }
    }
    RenderMap(map);
    RenderPlayer(player);
    RenderRays(player, rays);
    EndDrawing();
    ClearColorBuffer(colorBuffer);
}
