/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:49:50 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 15:52:22 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	player_position(t_player *player, t_map map)
{
	player->x = map.stock_j * map.tile_size + (map.tile_size / 2);
	player->y = map.stock_i * map.tile_size + (map.tile_size / 2);
}

void	setup(t_player *player, t_map map)
{
	player_position(player, map);
	player->width = 1;
	player->height = 1;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->walk_direction_side = 0;
	if (map.position == 'N')
		player->rotation_angle = 1.5 * PI;
	else if (map.position == 'S')
		player->rotation_angle = 0.5 * PI;
	else if (map.position == 'E')
		player->rotation_angle = 0;
	else if (map.position == 'W')
		player->rotation_angle = PI;
	player->walk_speed = 60;
	player->turn_speed = 5 * (PI / 180);
}
