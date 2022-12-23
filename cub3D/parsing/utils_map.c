/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 23:51:41 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/24 00:17:34 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting/main.h"

int	check_extention(char *av)
{
	int		i;
	char	*str;

	i = ft_strlen(av);
	str = av + i - 4;
	if (!ft_strncmp(str, ".cub", 4))
		return (0);
	else
		return (1);
}

void	free_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	init(t_map *texturs)
{
	texturs->NO = NULL;
	texturs->SO = NULL;
	texturs->WE = NULL;
	texturs->EA = NULL;
	texturs->C = 0;
	texturs->F = 0;
	texturs->only_map_len = 0;
}

int	ft_error_fd(int fd)
{
	if (0 > fd)
		return (printf("Error\n file discriptor"), exit(1), 1);
	return (0);
}

int	ft_strsearch(char *str)
{
	int	i;
	int	ver;

	ver = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			ver++;
		if (str[i + 1] && str[i] == ',' && str[i + 1] == ',')
			return (1);
		i++;
	}
	if (ver != 2)
		return (1);
	return (0);
}