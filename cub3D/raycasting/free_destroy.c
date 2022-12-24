/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:06:39 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 12:09:12 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_mlx(t_game *game)
{
	if (game->data.mlx)
	{
		mlx_destroy_image(game->data.mlx, game->data.img);
		mlx_clear_window(game->data.mlx, game->data.window);
		mlx_destroy_window(game->data.mlx, game->data.window);
		free_2d(game->map.my_map);
	}
}

void	exit_game(t_game *game)
{
	printf("Exit Game\n");
	free_mlx(game);
	free(game->ray);
	free(game->map.ea);
	free(game->map.we);
	free(game->map.no);
	free(game->map.so);
	exit (0);
}

void	display_error(char *msg)
{
	printf("%s", msg);
	exit(0);
}

int	ft_cross(t_game *game)
{
	printf("Exit Game\n");
	free_mlx(game);
	free(game->ray);
	exit(0);
	return (0);
}

void	free_check(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
