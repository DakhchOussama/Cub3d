#include "main.h"

void castRay(float rayAngle, int id, t_game *game)
{
    rayAngle = normalize_angle(rayAngle);
    game->raycast.isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    game->raycast.isRayFacingUp = !game->raycast.isRayFacingDown;
    game->raycast.isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    game->raycast.isRayFacingLeft = !game->raycast.isRayFacingRight;
    horizontal_intersection(game, rayAngle);
    vertical_intersection(game, rayAngle);
    verify_lower_intersection(game, rayAngle, id);
}

void castAllRays(t_game *game)
{
    int columnId;
    float rayAngle;
	int num_rays;

	num_rays = game->map.window_width;
    rayAngle = game->player.rotationAngle - (FOV / 2);
    columnId = 0;
    while (columnId < num_rays)
    {
        castRay(rayAngle, columnId, game);
        rayAngle += FOV / num_rays;
        columnId++;
    }
}

void setup_rays(t_ray *raycast)
{
    raycast->wallHitX = 0;
    raycast->wallHitY = 0;
    raycast->foundWallHit = FALSE;
    raycast->WallContent = 0;
}

float distance_between_points(float x, float y, float x2, float y2)
{
	return(sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y)));
}

void allocate_rays(t_game *game)
{
	game->ray = malloc((game->map.window_width + 1) * sizeof(t_ray));
}