/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odakhch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:37:46 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/24 15:42:04 by odakhch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	moveplayer(t_game *game, int *direction, int num)
{
	*direction = num;
	move(game);
	render(game);
}

int	key_press(int keyboard, t_game *game)
{
	if (keyboard == 0)
		moveplayer(game, \
		&game->player.walk_direction_side, -1);
	if (keyboard == 2)
		moveplayer(game, \
		&game->player.walk_direction_side, +1);
	if (keyboard == 13)
		moveplayer(game, \
		&game->player.walk_direction, +1);
	if (keyboard == 1)
		moveplayer(game, \
		&game->player.walk_direction, -1);
	if (keyboard == 124)
		moveplayer(game, \
		&game->player.turn_direction, +1);
	if (keyboard == 123)
		moveplayer(game, \
		&game->player.turn_direction, -1);
	if (keyboard == 53)
		exit_game(game);
	return (1);
}

int	key_release(int keyboard, t_game *game)
{
	if (keyboard == 0)
		game->player.walk_direction_side = 0;
	else if (keyboard == 2)
		game->player.walk_direction_side = 0;
	else if (keyboard == 13)
		game->player.walk_direction = 0;
	else if (keyboard == 1)
		game->player.walk_direction = 0;
	else if (keyboard == 123)
		game->player.turn_direction = 0;
	else if (keyboard == 124)
		game->player.turn_direction = 0;
	return (1);
}

void	process_input(t_game *game)
{
	mlx_hook(game->data.window, 17, 0L, ft_cross, game);
	mlx_hook(game->data.window, 2, 1L << 0, key_press, game);
	mlx_hook(game->data.window, 3, 1L << 1, key_release, game);
}
