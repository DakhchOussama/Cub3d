#include "main.h"

void horizontal_intersection(t_game *game, float ray_angle)
{
	int max_width;
	int max_height;

    setup_rays(&game->horizantal);
    game->horizantal.yintercept = floor(game->player.y / game->map.tile_size) * game->map.tile_size;
    if (game->raycast.isRayFacingDown)
        game->horizantal.yintercept += game->map.tile_size;
    game->horizantal.xintercept = game->player.x + (game->horizantal.yintercept - game->player.y) / tan(ray_angle); //???
    game->horizantal.ystep = game->map.tile_size;
    if (game->raycast.isRayFacingUp)
        game->horizantal.ystep *= -1;
	game->horizantal.xstep = game->map.tile_size / tan(ray_angle);
    if (game->raycast.isRayFacingLeft && game->horizantal.xstep > 0)
        game->horizantal.xstep *= -1;
    if (game->raycast.isRayFacingRight && game->horizantal.xstep < 0)
        game->horizantal.xstep *= -1;
    max_width = game->map.tile_size * game->map.num_cols;
    max_height = game->map.tile_size * game->map.height;
	game->horizantal.nextTouchX = game->horizantal.xintercept;
	game->horizantal.nextTouchY = game->horizantal.yintercept;
    horizontal_intersection2(game, max_width, max_height);
}

void vertical_intersection(t_game *game, float ray_angle)
{
	int max_width;
	int max_height;

    setup_rays(&game->vertical);
    game->vertical.xintercept = floor(game->player.x / game->map.tile_size) * game->map.tile_size;
    if (game->raycast.isRayFacingRight)
        game->vertical.xintercept += game->map.tile_size;
    game->vertical.yintercept = game->player.y + (game->vertical.xintercept - game->player.x) * tan(ray_angle);
    game->vertical.xstep = game->map.tile_size;
    if (game->raycast.isRayFacingLeft)
        game->vertical.xstep *= -1;
	game->vertical.ystep = game->map.tile_size * tan(ray_angle);
    if (game->raycast.isRayFacingUp && game->vertical.ystep > 0)
        game->vertical.ystep *= -1;
    if (game->raycast.isRayFacingDown && game->vertical.ystep < 0)
        game->vertical.ystep *= -1;
	game->vertical.nextTouchX = game->vertical.xintercept;
	game->vertical.nextTouchY = game->vertical.yintercept;
    max_width = game->map.tile_size * game->map.num_cols;
    max_height = game->map.tile_size * game->map.height;
    vertical_intersection2(game, max_width, max_height);
}

void horizontal_intersection2(t_game *game , int max_width, int max_height)
{
    while (game->horizantal.nextTouchX >= 0 && game->horizantal.nextTouchX <= max_width && game->horizantal.nextTouchY >= 0 \
     && game->horizantal.nextTouchY <= max_height)
    {
        game->horizantal.xtocheck = game->horizantal.nextTouchX;
        if (game->raycast.isRayFacingUp)
            game->horizantal.ytocheck = game->horizantal.nextTouchY - 1;
        else
            game->horizantal.ytocheck = game->horizantal.nextTouchY;
        if (has_collision(game, game->horizantal.xtocheck, game->horizantal.ytocheck, '1'))
        {
            game->horizantal.wallHitX = game->horizantal.nextTouchX;
            game->horizantal.wallHitY = game->horizantal.nextTouchY;
			size_t tmp = 0;
			if ((int)floor(game->horizantal.ytocheck / game->map.tile_size) < game->map.height && (int)floor(game->horizantal.ytocheck / game->map.tile_size) > 0)
				tmp = ft_strlen(game->map.my_map[(int)floor(game->horizantal.ytocheck / game->map.tile_size)]);
			if (tmp > (size_t)floor(game->vertical.xtocheck / game->map.tile_size))
            	game->horizantal.WallContent = game->map.my_map[(int)floor(game->horizantal.ytocheck / game->map.tile_size)][(int)floor(game->vertical.xtocheck / game->map.tile_size)];
            game->horizantal.foundWallHit = TRUE;
            break;
        }
        game->horizantal.nextTouchX += game->horizantal.xstep;
        game->horizantal.nextTouchY += game->horizantal.ystep;
    }
}
void vertical_intersection2(t_game *game , int max_width, int max_height)
{
    while (game->vertical.nextTouchX >= 0 && game->vertical.nextTouchX <= max_width \
		&& game->vertical.nextTouchY >= 0 && game->vertical.nextTouchY <= max_height)
    {
        game->vertical.ytocheck = game->vertical.nextTouchY;
        if (game->raycast.isRayFacingLeft)
            game->vertical.xtocheck = game->vertical.nextTouchX - 1;
        else
            game->vertical.xtocheck = game->vertical.nextTouchX;
        if (has_collision(game, game->vertical.xtocheck, game->vertical.ytocheck, '1'))
        {
            game->vertical.wallHitX = game->vertical.nextTouchX;
            game->vertical.wallHitY = game->vertical.nextTouchY;
            game->vertical.WallContent = game->map.my_map[(int)floor(game->vertical.ytocheck / game->map.tile_size)][(int)floor(game->vertical.xtocheck / game->map.tile_size)];
            game->vertical.foundWallHit = TRUE;
            break;
        }
        game->vertical.nextTouchX += game->vertical.xstep;
        game->vertical.nextTouchY += game->vertical.ystep;
    }
}

void put_on_struct(t_ray *ray, t_game *game, int id, int choose)
{
	game->ray[id].wallHitX = ray->wallHitX;
	game->ray[id].wallHitY = ray->wallHitY;
	game->ray[id].distance = ray->distance;
	game->ray[id].WallContent = ray->WallContent;
	game->ray[id].wasHitVertical = choose;
}

void verify_lower_intersection(t_game *game, float rayAngle, int id)
{
    if (game->horizantal.foundWallHit)
		game->horizantal.distance = distance_between_points(game->player.x, game->player.y, game->horizantal.wallHitX, game->horizantal.wallHitY);
	else
		game->horizantal.distance = FLT_MAX;
	if (game->vertical.foundWallHit)
		game->vertical.distance = distance_between_points(game->player.x, game->player.y, game->vertical.wallHitX, game->vertical.wallHitY);
	else
		game->vertical.distance = FLT_MAX;
	if (game->vertical.distance == game->horizantal.distance)
		game->vertical.distance--;
	if (game->vertical.distance < game->horizantal.distance)
		put_on_struct(&game->vertical, game, id, TRUE);
	else
		put_on_struct(&game->horizantal, game, id, FALSE);
	game->ray[id].rayAngle = rayAngle;
	game->ray[id].ray_down = game->raycast.isRayFacingDown;
	game->ray[id].ray_up = game->raycast.isRayFacingUp;
	game->ray[id].ray_left = game->raycast.isRayFacingLeft;
	game->ray[id].ray_right = game->raycast.isRayFacingRight;
}