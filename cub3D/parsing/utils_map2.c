/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:07:42 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/24 16:22:11 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting/main.h"

void	pars_map_norm(t_map *stock, int i, char **av)
{
	int		fd;
	int		j;
	char	*str;

	j = 0;
	fd = open(av[1], O_RDWR);
	ft_error_fd(fd);
	while (i <= stock->only_map_len)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (pars_map_norm_again(str) == 1)
		{
			i++;
			free(str);
			continue ;
		}
		stock->only_map[j] = str;
		if (ft_strlen(stock->only_map[j]) > stock->longest)
			stock->longest = ft_strlen(stock->only_map[j]);
		i++;
		j++;
	}
	pars_map_norm_2(stock, &j);
}

void	*pars_map(t_map *stock, char **av)
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDWR);
	ft_error_fd(fd);
	line = get_next_line(fd);
	while (line)
	{
		stock->only_map_len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	if (stock->only_map_len == 0)
		return (printf("Error\nEmpty only_map"), exit(1), NULL);
	stock->only_map = (char **)malloc(sizeof(char *) * stock->only_map_len + 1);
	if (!stock->only_map)
		return (printf("Error:\nonly_map is not allocated\n"), exit(1), NULL);
	pars_map_norm(stock, 0, av);
	return (NULL);
}
