/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:46:17 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 13:47:03 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Error\nCheking the arguments"), 1);
	ft_parsing_frist(&game, av);
	createwindow(&game.data, game.map);
	if (setup_texture(&game, &game.text))
	{
		free_mlx(&game);
		display_error("error in texture");
	}
	chose_tile_size(&game, &game.text);
	setup(&game.player, game.map);
	allocate_rays(&game);
	render(&game);
	process_input(&game);
	mlx_loop(game.data.mlx);
	free_2d(game.map.only_map);
	return (0);
}
