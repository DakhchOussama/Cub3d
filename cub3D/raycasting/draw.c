/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:14:36 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 15:37:05 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_sky(t_game *game, t_pic *pic)
{
	pic->y = 0;
	while (pic->y < pic->wall_top_pixel)
	{
		my_mlx_pixel_put(&game->data, pic->i, pic->y, game->map.c);
		pic->y++;
	}
}

void	draw_wall(t_game *game, t_pic *pic, int wallStrpHeight)
{
	if (game->ray[pic->i].was_hit_vertical)
		pic->textoffset_x = (int)game->ray[pic->i].wall_hit_y \
				% game->map.tile_size;
	else
		pic->textoffset_x = (int)game->ray[pic->i].wall_hit_x \
				% game->map.tile_size;
	if (game->ray[pic->i].ray_up && \
		!game->ray[pic->i].was_hit_vertical)
		game->text.now = game->text.north;
	else if (game->ray[pic->i].ray_down && \
		!game->ray[pic->i].was_hit_vertical)
		game->text.now = game->text.south;
	if (game->ray[pic->i].ray_right && \
		game->ray[pic->i].was_hit_vertical)
		game->text.now = game->text.east;
	if (game->ray[pic->i].ray_left && \
		game->ray[pic->i].was_hit_vertical)
		game->text.now = game->text.west;
	put_pixel(game, pic, wallStrpHeight);
}

void	ground(t_game *game, t_pic *pic)
{
	while (pic->y < game->map.window_height)
	{
		my_mlx_pixel_put(&game->data, pic->i, pic->y, game->map.f);
		pic->y++;
	}
}

int	found_wall_strip_height(t_pic *pic, t_game *game)
{
	pic->correct_distance = game->ray[pic->i].distance * \
					cos(game->ray[pic->i].ray_angle - \
					game->player.rotation_angle);
	pic->distanceprojplan = (game->map.window_width / 2) / tan(FOV / 2);
	pic->projection_wall = (game->map.tile_size / pic->correct_distance) \
						* pic->distanceprojplan;
	return ((int)pic->projection_wall);
}

void	map_3d(t_game *game)
{
	t_pic	pic;
	int		num_rays;
	int		wall_strip_height;

	num_rays = game->map.window_width;
	pic.i = 0;
	while (pic.i < num_rays)
	{
		wall_strip_height = found_wall_strip_height(&pic, game);
		pic.wall_top_pixel = (game->map.window_height / 2) \
							- (wall_strip_height / 2);
		if (pic.wall_top_pixel < 0)
			pic.wall_top_pixel = 0;
		pic.wall_bottom_pixel = (game->map.window_height / 2) \
							+ (wall_strip_height / 2);
		if (pic.wall_bottom_pixel > game->map.window_height)
			pic.wall_bottom_pixel = game->map.window_height;
		draw_sky(game, &pic);
		draw_wall(game, &pic, wall_strip_height);
		ground(game, &pic);
		pic.i++;
	}
}
