#include "ray.h"
#include "constants.h"
#include "map.h"
#include <float.h>

typedef struct intersection_t
{
    bool hitWall;
    Vector2 location;
    int wallContent;
} intersection_t;

float NormalizeAngle(float angle)
{
    angle = remainder(angle, PI * 2);
    if (angle < 0)
    {
        angle += PI * 2;
    }
    return angle;
}

bool IsRayFacingDown(float rayAngle)
{
    return rayAngle > 0 && rayAngle < PI;
}

bool IsRayFacingUp(float rayAngle)
{
    return !IsRayFacingDown(rayAngle);
}

bool IsRayFacingRight(float rayAngle)
{
    return rayAngle < (0.5 * PI) || rayAngle > (1.5 * PI);
}

bool IsRayFacingLeft(float rayAngle)
{
    return !IsRayFacingRight(rayAngle);
}

intersection_t CalculateHorizontalIntersection(map_t map, Vector2 origin, float rayAngle)
{
    int hitWall = false;
    Vector2 wallHitLocation = Vector2Zero();
    int wallContent = 0;

    Vector2 intercept = Vector2Zero();
    intercept.y = floor(origin.y / TILE_SIZE) * TILE_SIZE;
    intercept.y += IsRayFacingDown(rayAngle) ? TILE_SIZE : 0;
    intercept.x = origin.x + (intercept.y - origin.y) / tan(rayAngle);

    Vector2 step = Vector2Zero();
    step.y = TILE_SIZE;
    step.y *= IsRayFacingUp(rayAngle) ? -1 : 1;
    step.x = TILE_SIZE / tan(rayAngle);
    step.x *= (IsRayFacingLeft(rayAngle) && step.x > 0) ? -1 : 1;
    step.x *= (IsRayFacingRight(rayAngle) && step.x < 0) ? -1 : 1;

    Vector2 nextTouch = intercept;

    while (nextTouch.x >= 0 && nextTouch.x <= WINDOW_WIDTH && nextTouch.y >= 0 && nextTouch.y <= WINDOW_HEIGHT)
    {
        Vector2 locationToCheck = nextTouch;
        locationToCheck.y += (IsRayFacingUp(rayAngle) ? -1 : 0);
        if (HasWallAtLocation(map, locationToCheck))
        {
            wallHitLocation.x = nextTouch.x;
            wallHitLocation.y = nextTouch.y;
            wallContent = MapContentAtLocation(map, locationToCheck);
            hitWall = true;
            break;
        }
        nextTouch.x += step.x;
        nextTouch.y += step.y;
    }
    return (intersection_t){hitWall, wallHitLocation, wallContent};
}

intersection_t CalculateVerticalIntersection(map_t map, Vector2 origin, float rayAngle)
{
    int hitWall = false;
    Vector2 wallHitLocation = Vector2Zero();
    int wallContent = 0;

    Vector2 intercept = Vector2Zero();
    intercept.x = floor(origin.x / TILE_SIZE) * TILE_SIZE;
    intercept.x += IsRayFacingRight(rayAngle) ? TILE_SIZE : 0;
    intercept.y = origin.y + (intercept.x - origin.x) * tan(rayAngle);

    Vector2 step = Vector2Zero();
    step.x = TILE_SIZE;
    step.x *= IsRayFacingLeft(rayAngle) ? -1 : 1;
    step.y = TILE_SIZE * tan(rayAngle);
    step.y *= (IsRayFacingUp(rayAngle) && step.y > 0) ? -1 : 1;
    step.y *= (IsRayFacingDown(rayAngle) && step.y < 0) ? -1 : 1;

    Vector2 nextTouch = intercept;

    while (nextTouch.x >= 0 && nextTouch.x <= WINDOW_WIDTH && nextTouch.y >= 0 && nextTouch.y <= WINDOW_HEIGHT)
    {
        Vector2 locationToCheck = nextTouch;
        locationToCheck.x += (IsRayFacingLeft(rayAngle) ? -1 : 0);
        if (HasWallAtLocation(map, locationToCheck))
        {
            wallHitLocation.x = nextTouch.x;
            wallHitLocation.y = nextTouch.y;
            wallContent = MapContentAtLocation(map, locationToCheck);
            hitWall = true;
            break;
        }
        nextTouch.x += step.x;
        nextTouch.y += step.y;
    }
    return (intersection_t){hitWall, wallHitLocation, wallContent};
}

void CastRay(ray_t *ray, map_t map, Vector2 origin, float rayAngle)
{
    rayAngle = NormalizeAngle(rayAngle);
    intersection_t horizontal = CalculateHorizontalIntersection(map, origin, rayAngle);
    intersection_t vertical = CalculateVerticalIntersection(map, origin, rayAngle);

    float horizontalHitDistance = horizontal.hitWall ? Vector2Distance(origin, horizontal.location) : FLT_MAX;
    float verticalHitDistance = vertical.hitWall ? Vector2Distance(origin, vertical.location) : FLT_MAX;

    if (verticalHitDistance < horizontalHitDistance)
    {
        ray->distance = verticalHitDistance;
        ray->wallHitLocation = vertical.location;
        ray->wallContent = vertical.wallContent;
        ray->wasHitVertical = true;
    }
    else
    {
        ray->distance = horizontalHitDistance;
        ray->wallHitLocation = horizontal.location;
        ray->wallContent = horizontal.wallContent;
        ray->wasHitVertical = false;
    }
    ray->angle = rayAngle;
}

void CastRays(player_t *player, map_t map, ray_t *rays)
{
    for (int i = 0; i < RAY_COUNT; i++)
    {
        ray_t *ray = &rays[i];
        float rayAngle = player->rotationAngle + atan((i - RAY_COUNT / 2) / DISTANCE_TO_PROJECTION_PLANE);
        CastRay(ray, map, player->location, rayAngle);
        rayAngle += FOV / RAY_COUNT;
    }
}
