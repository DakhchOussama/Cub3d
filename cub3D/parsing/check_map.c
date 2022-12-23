/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:42:02 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/24 00:17:27 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting/main.h"
#include <stdio.h>
#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "get_next_line/get_next_line.h"

void	*line_c_and_f(char **spl, char *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (++i <= 3)
		if (ft_atoi(spl[i]) < 0 || ft_atoi(spl[i]) > 255)
			return (printf("Error\nR.G.B values"), free_2d(spl), exit(1), NULL);
	if (ft_strsearch(map))
		return (printf("Error\nR.G.B sytax"), free_2d(spl), exit(1), NULL);
	return (NULL);
}

int check_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = '1';
		i++;
	}
	return (0);
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
	pars_map(pars, av);
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
	// 	int i = 0;
	// int j;
	// while (pars->only_map[i] != NULL)
	// {
	// 	j = 0;
	// 	while (pars->only_map[i][j] != '\0')
	// 	{
	// 		printf("%c",pars->only_map[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	return (0);
}

int	ft_parsing_frist(t_game *game, int ac, char **av)
{
	int		fd;
	int		i;
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
	i = 0;
	while (game->map.my_map[i])
	{
		if (check_space(game->map.my_map[i]))
			break;
		i++;
	}
	return (0);
}
