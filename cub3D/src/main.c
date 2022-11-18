#include "main.h"

void setup_map(t_map *map)
{
    map->num_cols = 20;
    map->num_rows = 13;
    map->title_size = 60;
    map->window_height = map->num_rows * map->title_size;
    map->window_width = map->num_cols * map->title_size;
}

int	direction(int keyboard, t_game *game)
{
	if (keyboard == 53)
		exit_game(game->data);
	if (keyboard == 0)
        move_right(game);
	else if (keyboard == 2)
        move_left(game);
	else if (keyboard == 13)
        move_up(game);
	else if (keyboard == 1)
        move_down(game);
    else if (keyboard == 123)
        move_rotation_left(game);
    else if (keyboard == 124)
        move_rotation_right(game);
	return (0);
}

void update (t_player *player, t_data data, t_game *game)
{
    mlx_hook(game->data.window, 17, 0L, &ft_cross, game);
    mlx_hook(game->data.window, 2, 1L << 0, direction, game);
}

int main()
{
    t_data mlx;
    t_player player;
    t_game game;
    t_map map;
    setup_map(&map);
    CreateWindow(&mlx, map);
    setup(&player, map);
    render(mlx, &player, map);
    game.data = mlx;
    game.map = map;
    game.player = player;
    update(&game.player, mlx, &game);
    mlx_loop(game.data.mlx);
    return (0);
}