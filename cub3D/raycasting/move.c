/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:47:14 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 14:57:33 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

int	has_collision(t_game *game, float x, float y, char num)
{
	int	map_x;
	int	map_y;
	int	ret;

	if (x < 0 || x >= game->map.window_width * game->map.tile_size || \
		y < 0 || y >= game->map.window_height * game->map.tile_size)
		return (TRUE);
	map_x = x / game->map.tile_size;
	map_y = y / game->map.tile_size;
	if (game->map.my_map[map_y] && (ft_strlen(game->map.my_map[map_y]) > \
		(size_t)map_x && (size_t)map_x >= 0) && game->map.my_map[map_y][map_x] \
		&& game->map.my_map[map_y][map_x] == num)
		ret = TRUE;
	else
		ret = FALSE;
	return (ret);
}

int	wall_collection(t_game *game, float x, float y, char num)
{
	float	map_x;
	float	map_y;

	map_x = x / game->map.tile_size;
	map_y = y / game->map.tile_size;
	if (game->map.my_map[(int)(map_y + 0.2)][(int)(map_x)] == num)
		return (TRUE);
	if (game->map.my_map[(int)(map_y - 0.2)][(int)(map_x)] == num)
		return (TRUE);
	if (game->map.my_map[(int)(map_y)][(int)(map_x + 0.2)] == num)
		return (TRUE);
	if (game->map.my_map[(int)(map_y)][(int)(map_x - 0.2)] == num)
		return (TRUE);
	return (FALSE);
}

void	move(t_game *game)
{
	float	movestep;
	float	newplayer_x;
	float	newplayer_y;

	game->player.rotation_angle += game->player.turn_direction \
						* game->player.turn_speed;
	game->player.rotation_angle = normalize_angle(game->player.rotation_angle);
	movestep = game->player.walk_direction * game->player.walk_speed;
	newplayer_x = game->player.x + cos(game->player.rotation_angle) * movestep;
	newplayer_y = game->player.y + sin(game->player.rotation_angle) * movestep;
	if (!has_collision(game, newplayer_x, newplayer_y, '1') \
		&& !wall_collection(game, newplayer_x, newplayer_y, '1'))
	{
		game->player.x = newplayer_x;
		game->player.y = newplayer_y;
	}
	check_right_left(game);
}
