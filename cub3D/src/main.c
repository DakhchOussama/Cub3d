#include "main.h"

int main(int argc, char **av)
{
    int         fd;
    t_game      game;
    char        *table;

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        display_error("Error in File Descriptor\n");
    table = read_file(fd);
    (void)argc;
    if (!table)
        display_error("Error in read File\n");
    setup_map(&game.map, table);
    CreateWindow(&game.data, game.map);
	if (setup_texture(&game, &game.text))
		display_error("error in texture");
	chose_tile_size(&game, &game.text);
    setup(&game.player, game.map);
	allocate_rays(&game);
    render(&game);
    process_input(&game);
    mlx_loop(game.data.mlx);
    return (0);
}