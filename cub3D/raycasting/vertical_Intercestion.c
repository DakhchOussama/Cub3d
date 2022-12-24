/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_Intercestion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:45:46 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 17:52:54 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	vertical_intersection(t_game *game, float ray_angle)
{
	int	max_width;
	int	max_height;

	setup_rays(&game->vertical);
	game->vertical.xintercept = floor(game->player.x / game->map.tile_size) \
								* game->map.tile_size;
	if (game->raycast.ray_facing_right)
		game->vertical.xintercept += game->map.tile_size;
	game->vertical.yintercept = game->player.y + (game->vertical.xintercept \
		- game->player.x) * tan(ray_angle);
	game->vertical.xstep = game->map.tile_size;
	if (game->raycast.ray_facing_left)
		game->vertical.xstep *= -1;
	game->vertical.ystep = game->map.tile_size * tan(ray_angle);
	if (game->raycast.ray_facing_up && game->vertical.ystep > 0)
		game->vertical.ystep *= -1;
	if (game->raycast.ray_facing_down && game->vertical.ystep < 0)
		game->vertical.ystep *= -1;
	game->vertical.next_touch_x = game->vertical.xintercept;
	game->vertical.next_touch_y = game->vertical.yintercept;
	max_width = game->map.tile_size * game->map.num_cols;
	max_height = game->map.tile_size * game->map.height;
	vertical_intersection2(game, max_width, max_height);
}

void	vertical_intersection2(t_game *game, int max_width, int max_height)
{
	while (game->vertical.next_touch_x >= 0 && game->vertical.next_touch_x <= \
			max_width && game->vertical.next_touch_y >= 0 && \
			game->vertical.next_touch_y <= max_height)
	{
		game->vertical.ytocheck = game->vertical.next_touch_y;
		if (game->raycast.ray_facing_left)
			game->vertical.xtocheck = game->vertical.next_touch_x - 1;
		else
			game->vertical.xtocheck = game->vertical.next_touch_x;
		if (has_collision(game, game->vertical.xtocheck, \
					game->vertical.ytocheck, '1'))
		{
			game->vertical.wall_hit_x = game->vertical.next_touch_x;
			game->vertical.wall_hit_y = game->vertical.next_touch_y;
			check_ray(game);
			game->vertical.found_wall_hit = TRUE;
			break ;
		}
		game->vertical.next_touch_x += game->vertical.xstep;
		game->vertical.next_touch_y += game->vertical.ystep;
	}
}

void	verify_lower_intersection(t_game *game, float rayAngle, int id)
{
	if (game->horizantal.found_wall_hit)
		game->horizantal.distance = distance_between_points(game->player.x, \
			game->player.y, game->horizantal.wall_hit_x, \
			game->horizantal.wall_hit_y);
	else
		game->horizantal.distance = FLT_MAX;
	if (game->vertical.found_wall_hit)
		game->vertical.distance = distance_between_points(game->player.x, \
			game->player.y, game->vertical.wall_hit_x, \
			game->vertical.wall_hit_y);
	else
		game->vertical.distance = FLT_MAX;
	if (game->vertical.distance == game->horizantal.distance)
		game->vertical.distance--;
	if (game->vertical.distance < game->horizantal.distance)
		put_on_struct(&game->vertical, game, id, TRUE);
	else
		put_on_struct(&game->horizantal, game, id, FALSE);
	game->ray[id].ray_angle = rayAngle;
	game->ray[id].ray_down = game->raycast.ray_facing_down;
	game->ray[id].ray_up = game->raycast.ray_facing_up;
	game->ray[id].ray_left = game->raycast.ray_facing_left;
	game->ray[id].ray_right = game->raycast.ray_facing_right;
}
