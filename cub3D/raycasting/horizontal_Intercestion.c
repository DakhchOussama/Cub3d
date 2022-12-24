/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_Intercestion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:44:07 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 13:45:41 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	horizontal_intersection(t_game *game, float ray_angle)
{
	int	max_width;
	int	max_height;

	setup_rays(&game->horizantal);
	game->horizantal.yintercept = floor(game->player.y / game->map.tile_size) \
							* game->map.tile_size;
	if (game->raycast.ray_facing_down)
		game->horizantal.yintercept += game->map.tile_size;
	game->horizantal.xintercept = game->player.x + (game->horizantal.yintercept \
		- game->player.y) / tan(ray_angle);
	game->horizantal.ystep = game->map.tile_size;
	if (game->raycast.ray_facing_up)
		game->horizantal.ystep *= -1;
	game->horizantal.xstep = game->map.tile_size / tan(ray_angle);
	if (game->raycast.ray_facing_left && game->horizantal.xstep > 0)
		game->horizantal.xstep *= -1;
	if (game->raycast.ray_facing_right && game->horizantal.xstep < 0)
		game->horizantal.xstep *= -1;
	max_width = game->map.tile_size * game->map.num_cols;
	max_height = game->map.tile_size * game->map.height;
	game->horizantal.next_touch_x = game->horizantal.xintercept;
	game->horizantal.next_touch_y = game->horizantal.yintercept;
	horizontal_intersection2(game, max_width, max_height);
}

void	check_ray(t_game *game)
{
	size_t	tmp;

	tmp = 0;
	if ((int)floor(game->horizantal.ytocheck / game->map.tile_size) < \
		game->map.height && (int)floor(game->horizantal.ytocheck \
		/ game->map.tile_size) > 0)
		tmp = ft_strlen(game->map.my_map[(int)floor(game->horizantal.ytocheck \
		/ game->map.tile_size)]);
	if (tmp > (size_t)floor(game->vertical.xtocheck / game->map.tile_size))
		game->horizantal.wall_content = game->map.my_map[(int)floor(\
		game->horizantal.ytocheck / game->map.tile_size)][(int) floor(\
		game->vertical.xtocheck / game->map.tile_size)];
}

void	horizontal_intersection2(t_game *game, int max_width, int max_height)
{
	while (game->horizantal.next_touch_x >= 0 && game->horizantal.next_touch_x \
		<= max_width && game->horizantal.next_touch_y >= 0 \
		&& game->horizantal.next_touch_y <= max_height)
	{
		game->horizantal.xtocheck = game->horizantal.next_touch_x;
		if (game->raycast.ray_facing_up)
			game->horizantal.ytocheck = game->horizantal.next_touch_y - 1;
		else
			game->horizantal.ytocheck = game->horizantal.next_touch_y;
		if (has_collision(game, game->horizantal.xtocheck, \
					game->horizantal.ytocheck, '1'))
		{
			game->horizantal.wall_hit_x = game->horizantal.next_touch_x;
			game->horizantal.wall_hit_y = game->horizantal.next_touch_y;
			check_ray(game);
			game->horizantal.found_wall_hit = TRUE;
			break ;
		}
		game->horizantal.next_touch_x += game->horizantal.xstep;
		game->horizantal.next_touch_y += game->horizantal.ystep;
	}
}

void	put_on_struct(t_ray *ray, t_game *game, int id, int choose)
{
	game->ray[id].wall_hit_x = ray->wall_hit_x;
	game->ray[id].wall_hit_y = ray->wall_hit_y;
	game->ray[id].distance = ray->distance;
	game->ray[id].wall_content = ray->wall_content;
	game->ray[id].was_hit_hertical = choose;
}
