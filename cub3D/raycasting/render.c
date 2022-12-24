/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:47:49 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 15:48:52 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD
#include "main.h"
=======
void draw_sky(t_game *game, t_pic *pic)
{
	pic->y = 0;
	while (pic->y < pic->Wall_top_pixel)
	{
		my_mlx_pixel_put(&game->data, pic->i, pic->y, game->map.c);
		pic->y++;
	}
}
>>>>>>> f389e5d2bdbb86db452d027603f50d0e239615db

void	check_right_left(t_game *game)
{
	float	side_step;
	float	new_player_x;
	float	new_player_y;

	side_step = game->player.walk_direction_side * game->player.walk_speed;
	new_player_x = game->player.x \
			+ cos(game->player.rotation_angle + 0.5 * PI) * side_step;
	new_player_y = game->player.y \
			+ sin(game->player. rotation_angle + 0.5 * PI) * side_step;
	if (!has_collision(game, new_player_x, new_player_y, '1') \
		&& !wall_collection(game, new_player_x, new_player_y, '1'))
	{
<<<<<<< HEAD
		game->player.x = new_player_x;
		game->player.y = new_player_y;
=======
		my_mlx_pixel_put(&game->data, pic->i, pic->y, game->map.f);
		pic->y++;
>>>>>>> f389e5d2bdbb86db452d027603f50d0e239615db
	}
}

void	render(t_game *game)
{
	castallrays(game);
	map_3d(game);
	mlx_put_image_to_window(game->data.mlx, game->data.window, \
	game->data.img, 0, 0);
}
