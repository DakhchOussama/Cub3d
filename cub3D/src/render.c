#include "main.h"

void draw_sky(t_game *game, t_pic *pic)
{
	pic->y = 0;
	while (pic->y < pic->Wall_top_pixel)
	{
		my_mlx_pixel_put(&game->data, pic->i, pic->y, 0x34E2DF);
		pic->y++;
	}
}

void draw_wall(t_game *game, t_pic *pic, int wallStrpHeight)
{
	if (game->ray[pic->i].wasHitVertical)
		pic->textOff_X = (int)game->ray[pic->i].wallHitY % game->map.tile_size;
	else
		pic->textOff_X = (int)game->ray[pic->i].wallHitX % game->map.tile_size;
	if (game->ray[pic->i].ray_up && !game->ray[pic->i].wasHitVertical)
		game->text.now = game->text.north;
	else if (game->ray[pic->i].ray_down && !game->ray[pic->i].wasHitVertical)
		game->text.now = game->text.south;
	if (game->ray[pic->i].ray_right && game->ray[pic->i].wasHitVertical)
		game->text.now = game->text.east;
	if (game->ray[pic->i].ray_left && game->ray[pic->i].wasHitVertical)
		game->text.now = game->text.west;
	pic->y = pic->Wall_top_pixel;
	while (pic->y < pic->Wall_bottom_pixel)
	{
		pic->distance_from_top = pic->y + (wallStrpHeight / 2) - (game->map.window_height / 2);
		pic->textOff_Y = pic->distance_from_top * ((float)game->text.now.height / wallStrpHeight);
		pic->color = my_mlx_pixel_pick(&game->text.now, pic->textOff_X, pic->textOff_Y);
		my_mlx_pixel_put(&game->data, pic->i, pic->y, pic->color);
		pic->y++;
	}
}

void ground(t_game *game, t_pic *pic)
{
	while (pic->y < game->map.window_height)
	{
		my_mlx_pixel_put(&game->data, pic->i, pic->y, 0x5C5069);
		pic->y++;
	}
}

void Map3D(t_game *game)
{
	t_pic pic;
	int num_rays;
	int wallStripHeight;

	num_rays = game->map.window_width;
	pic.i = 0;
	while (pic.i < num_rays)
	{
		pic.correctDistance = game->ray[pic.i].distance * cos(game->ray[pic.i].rayAngle - game->player.rotationAngle);
		pic.distanceprojplan = (game->map.window_width / 2) / tan(FOV / 2);
		pic.projectionWall = (game->map.tile_size / pic.correctDistance) * pic.distanceprojplan;
		wallStripHeight = (int)pic.projectionWall;
		pic.Wall_top_pixel = (game->map.window_height / 2) - (wallStripHeight / 2);
		if (pic.Wall_top_pixel < 0)
			pic.Wall_top_pixel = 0;
		pic.Wall_bottom_pixel = (game->map.window_height / 2) + (wallStripHeight / 2); //??
		if (pic.Wall_bottom_pixel > game->map.window_height)
			pic.Wall_bottom_pixel = game->map.window_height;
		draw_sky(game, &pic);
		draw_wall(game, &pic, wallStripHeight);
		ground(game, &pic);
		pic.i++;
	}
}

void render(t_game *game)
{
	castAllRays(game);
	Map3D(game);
    mlx_put_image_to_window(game->data.mlx, game->data.window, game->data.img, 0, 0);
}