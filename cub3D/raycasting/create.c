/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:59:29 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 15:57:48 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	createwindow(t_data *mlx, t_map map)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		display_error("Error create MLX \n");
	mlx->window = mlx_new_window(mlx->mlx, map.window_width, \
			map.window_height, "Cub3D");
	if (!mlx->window)
		display_error("Error create MLX \n");
	mlx->img = mlx_new_image(mlx->mlx, map.window_width, map.window_height);
	if (!mlx->img)
		display_error("Error create Image \n");
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->zl, &mlx->ed);
	if (!mlx->addr)
		display_error("Error to take address");
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->zl + x * (data->bpp / 8));
	*(unsigned int *) dst = color;
}

int	my_mlx_pixel_pick(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->zl + x * (data->bpp / 8));
	return (*(unsigned int *) dst);
}

void	put_pixel(t_game *game, t_pic *pic, int wallStrpHeight)
{
	pic->y = pic->wall_top_pixel;
	while (pic->y < pic->wall_bottom_pixel)
	{
		pic->distance_from_top = pic->y + (wallStrpHeight / 2) - \
						(game->map.window_height / 2);
		pic->textoffset_y = pic->distance_from_top * \
				((float)game->text.now.height / wallStrpHeight);
		pic->color = my_mlx_pixel_pick(&game->text.now, \
				pic->textoffset_x, pic->textoffset_y);
		my_mlx_pixel_put(&game->data, pic->i, pic->y, pic->color);
		pic->y++;
	}
}
