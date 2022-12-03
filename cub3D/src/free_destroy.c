#include "main.h"

void	free_mlx(t_game *game)
{
	if (game->data.mlx)
	{
		mlx_destroy_image(game->data.mlx, game->data.img);
		mlx_destroy_window(game->data.mlx, game->data.window);
		mlx_clear_window(game->data.mlx, game->data.window);
		free(game->map.my_map);
		printf("Exit Game\n");
		exit(0);
	}
}

void exit_game(t_game *game)
{
	free_mlx(game);
}

void display_error(char *msg)
{
	printf("%s",msg);
	exit(EXIT_FAILURE);
}

int	ft_cross(t_game *game)
{
	free_mlx(game);
	return (0);
}

void destroyWindow(void *mlx, void *window)
{
    mlx_destroy_window(mlx, window);
}