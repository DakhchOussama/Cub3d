#include "main.h"

int setup_texture(t_game *game, t_text *text)
{
	text->north.img = mlx_xpm_file_to_image(game->data.mlx, game->map.NO, &text->north.width, &text->north.height);
	text->south.img = mlx_xpm_file_to_image(game->data.mlx, game->map.SO, &text->south.width, &text->south.height);
	text->east.img = mlx_xpm_file_to_image(game->data.mlx, game->map.EA, &text->east.width, &text->east.height);
	text->west.img = mlx_xpm_file_to_image(game->data.mlx, game->map.WE, &text->west.width, &text->west.height);
	if (!text->north.img || !text->south.img || !text->east.img || !text->west.img)
		return (1);
	text->north.addr = mlx_get_data_addr(text->north.img, &text->north.bpp, &text->north.zl, &text->north.ed);
	text->south.addr = mlx_get_data_addr(text->south.img, &text->south.bpp, &text->south.zl, &text->south.ed);
	text->east.addr = mlx_get_data_addr(text->east.img, &text->east.bpp, &text->east.zl, &text->east.ed);
	text->west.addr = mlx_get_data_addr(text->west.img, &text->west.bpp, &text->west.zl, &text->west.ed);
	return (0);
}

void put_textures_in_array(t_text *text)
{
	text->textur[0] = text->north.width;
	text->textur[1] = text->north.height;
	text->textur[2] = text->south.width;
	text->textur[3] = text->south.height;
	text->textur[4] = text->east.width;
	text->textur[5] = text->east.height;
	text->textur[6] = text->west.width;
	text->textur[7] = text->west.height;
}

void chose_tile_size(t_game *game, t_text *text)
{
	int j;
	int tab;

	put_textures_in_array(text);
	j = 0;
	while (j < 7)
	{
		if (text->textur[j] > text->textur[j + 1])
		{
			tab = text->textur[j];
			text->textur[j] = text->textur[j + 1];
			text->textur[j + 1] = tab;
		}
		j++;
	}
	game->map.tile_size = text->textur[0];
}