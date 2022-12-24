/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castRays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:42:28 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 16:45:57 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	castray(float rayAngle, int id, t_game *game)
{
	rayAngle = normalize_angle(rayAngle);
	game->raycast.ray_facing_down = (rayAngle > 0 && rayAngle < PI);
	game->raycast.ray_facing_up = !game->raycast.ray_facing_down;
	game->raycast.ray_facing_right = (rayAngle < 0.5 * PI || \
			rayAngle > 1.5 * PI);
	game->raycast.ray_facing_left = !game->raycast.ray_facing_right;
	horizontal_intersection(game, rayAngle);
	vertical_intersection(game, rayAngle);
	verify_lower_intersection(game, rayAngle, id);
}

void	castallrays(t_game *game)
{
	int		column_id;
	float	ray_angle;
	int		num_rays;

	num_rays = game->map.window_width;
	ray_angle = game->player.rotation_angle - (FOV / 2);
	column_id = 0;
	while (column_id < num_rays)
	{
		castray(ray_angle, column_id, game);
		ray_angle += FOV / num_rays;
		column_id++;
	}
}

void	setup_rays(t_ray *raycast)
{
	raycast->wall_hit_x = 0;
	raycast->wall_hit_y = 0;
	raycast->found_wall_hit = FALSE;
	raycast->wall_content = 0;
}

float	distance_between_points(float x, float y, float x2, float y2)
{
	return (sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y)));
}

void	allocate_rays(t_game *game)
{
	game->ray = malloc((game->map.window_width + 1) * sizeof(t_ray));
}
