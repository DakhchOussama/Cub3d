/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:42:02 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/26 23:39:22 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting/main.h"

void	*line_c_and_f(char **spl, char *map)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	j = 0;
	while (++j <= 3)
	{
		y = 0;
		while (spl[j][y])
		{
			if (ft_isdigit(spl[j][y]) == 0)
				return (printf("Error\nR.G.B is not digit"), \
				free_2d(spl), exit(1), NULL);
			y++;
		}
	}
	while (++i <= 3)
		if (ft_atoi(spl[i]) < 0 || ft_atoi(spl[i]) > 255)
			return (printf("Error\nR.G.B values"), free_2d(spl), exit(1), NULL);
	if (ft_strsearch(map))
		return (printf("Error\nR.G.B sytax"), free_2d(spl), exit(1), NULL);
	return (NULL);
}

void	check_newline_in_map(t_map *pars, int i, char **av)
{
	while (pars->my_map[i])
	{
		if (ft_strncmp(pars->my_map[i], "\n", 1) == 0)
		{
			printf("Error:\n new line in map");
			exit(1);
		}
		i++;
	}
	pars_map(pars, av);
}

void	ft_parsing_norm(t_map *pars, char **av)
{
	int	fd;
	int	i;
	int	j;

	i = 0;
	fd = open(av[1], O_RDWR);
	ft_error_fd(fd);
	while (i + 1 < pars->len)
	{
		pars->my_map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	pars->my_map[i] = NULL;
	i = -1;
	init(pars);
	while (pars->my_map[++i])
	{
		j = 0;
		while ((pars->my_map[i][j] == ' ' || pars->my_map[i][j] == '\t'))
				j++;
		if (pars->my_map[i][j] == '1' || pars->my_map[i][j] == '0')
			break ;
	}
	check_newline_in_map(pars, i, av);
}

int	ft_parsing(t_map *pars, char **av)
{
	int		fd;
	char	*line;
	int		i;

	pars->len = 0;
	fd = open(av[1], O_RDWR);
	ft_error_fd(fd);
	line = get_next_line(fd);
	while (line)
	{
		pars->len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (pars->len == 0)
		return (printf("Error\nEmpty map"), 1);
	pars->my_map = (char **)malloc(sizeof(char *) * (pars->len + 1));
	if (!pars->my_map)
		return (printf("Error:\nmap is not allocated\n"), 1);
	ft_parsing_norm(pars, av);
	i = -1;
	while (pars->my_map[++i])
		check_texture(pars, pars->my_map[i]);
	return (0);
}

int	ft_parsing_frist(t_game *game, int ac, char **av)
{
	int		fd;

	if (ac != 2)
		return (printf("Error\nCheking the arguments"), 1);
	fd = open(av[1], O_RDWR);
	ft_error_fd(fd);
	close(fd);
	if (check_extention(av[1]))
		display_error("Error\nExtention");
	if (ft_parsing(&game->map, av))
		return (1);
	free_2d(game->map.my_map);
	game->map.my_map = game->map.only_map;
	game->map.tile_size = 60;
	game->map.window_height = game->map.height * game->map.tile_size;
	game->map.window_width = game->map.num_cols * game->map.tile_size;
	return (0);
}
