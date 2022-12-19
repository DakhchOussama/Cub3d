#include "main.h"

void moveplayer(t_game *game, int *direction, int num)
{
	*direction = num;
	move(game);
	render(game);
}

int	key_press(int keyboard, t_game *game)
{
	if (keyboard == 0)
        moveplayer(game, &game->player.walkDirection_side , -1);
	if (keyboard == 2)
        moveplayer(game, &game->player.walkDirection_side , +1);
	if (keyboard == 13)
        moveplayer(game, &game->player.walkDirection , +1);
	if (keyboard == 1)
        moveplayer(game, &game->player.walkDirection ,-1);
    if (keyboard == 124)
        moveplayer(game, &game->player.turnDirection ,+1);
    if (keyboard == 123)
        moveplayer(game, &game->player.turnDirection ,-1);
	if (keyboard == 53)
		exit_game(game);
	return (1);
}

int key_release(int keyboard, t_game *game)
{
	if (keyboard == 0)
        game->player.walkDirection_side = 0;
	else if (keyboard == 2)
        game->player.walkDirection_side = 0;
	else if (keyboard == 13)
        game->player.walkDirection = 0;
	else if (keyboard == 1)
        game->player.walkDirection = 0;
    else if (keyboard == 123)
        game->player.turnDirection = 0;
    else if (keyboard == 124)
        game->player.turnDirection = 0;
	return (1);
}

void process_input(t_game *game)
{
    mlx_hook(game->data.window, 17, 0L, ft_cross, game);
    mlx_hook(game->data.window, 2, 1L << 0, key_press, game);
    mlx_hook(game->data.window, 3, 1L << 1, key_release, game);
}