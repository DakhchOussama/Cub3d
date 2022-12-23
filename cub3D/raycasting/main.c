#include "main.h"

int main(int ac, char **av)
{
    t_game      game;

	ft_parsing_frist(&game, ac, av);
	game.map.tile_size = 60;
	game.map.window_height = game.map.height * game.map.tile_size;
	game.map.window_width = game.map.num_cols * game.map.tile_size;
    CreateWindow(&game.data, game.map);
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