/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:49:24 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/24 16:17:58 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting/main.h"

int	check_middle_lines_norm(t_map *my_map, int *i, int *j)
{
	if (my_map->only_map[*i][*j] != ' ' && my_map->only_map[*i][*j] != '1')
	{
		if (my_map->only_map[*i][*j - 1] == ' ' || \
			my_map->only_map[*i][*j + 1] == ' ')
			return (printf("Error\nmap not closed"), \
				free_2d(my_map->only_map), exit(1), 1);
		if (((int)ft_strlen(my_map->only_map[*i - 1]) - 1 <= *j) || \
			((int)ft_strlen(my_map->only_map[*i + 1]) - 1 <= *j))
			return (printf("Error\nmap not closed"), \
				free_2d(my_map->only_map), exit(1), 1);
		else if (my_map->only_map[*i - 1][*j] == ' ' || \
			my_map->only_map[*i + 1][*j] == ' ')
			return (printf("Error\nmap not closed"), \
				free_2d(my_map->only_map), exit(1), 1);
	}
	return (0);
}

void	*check_middle_lines(t_map *my_map, int nbr, int i)
{
	int	j;

	while (my_map->only_map[++i])
	{
		j = 0;
		while (my_map->only_map[i][j] && my_map->only_map[i][j] != '\n')
		{
			if (my_map->only_map[i][j] == 'N' || \
				my_map->only_map[i][j] == 'S' || \
				my_map->only_map[i][j] == 'E' || my_map->only_map[i][j] == 'W')
			{
				my_map->stock_i = i;
				my_map->stock_j = j;
				verify_place(my_map->only_map[i][j], my_map);
				nbr++;
			}
			check_middle_lines_norm(my_map, &i, &j);
			j++;
		}
	}
	if (nbr != 1)
		return (printf("Error\nnbr of players"), \
			free_2d(my_map->only_map), exit(1), NULL);
	return (NULL);
}

void	*first_and_last(t_map *my_map)
{
	int		i;
	char	*trim;

	i = -1;
	while (my_map->only_map[0][++i] != '\n')
		if (my_map->only_map[0][i] != ' ' && my_map->only_map[0][i] != '1')
			return (printf("Error\nmap not closed"), \
				free_2d(my_map->only_map), exit(1), NULL);
	i = -1;
	while (my_map->only_map[my_map->height - 1][++i])
		if (my_map->only_map[my_map->height - 1][i] != ' ' && \
			my_map->only_map[my_map->height - 1][i] != '1')
			return (printf("Error\nmap not closed"), \
				free_2d(my_map->only_map), exit(1), NULL);
	i = -1;
	while (my_map->only_map[++i])
	{
		trim = ft_strtrim(my_map->only_map[i], " \n");
		if (trim[0] != '1' || trim[ft_strlen(trim) - 1] != '1')
			return (printf("Error\nmap not closed"), \
				free(trim), free_2d(my_map->only_map), exit(1), NULL);
		free(trim);
	}
	check_middle_lines(my_map, 0, -1);
	return (NULL);
}

int	pars_map_norm_again(char *str)
{
	if (ft_strncmp(str, "\n", 1) == 0 || ft_strncmp(str, "NO", 2) == 0 || \
	ft_strncmp(str, "SO", 2) == 0 || ft_strncmp(str, "WE", 2) == 0 || \
	ft_strncmp(str, "EA", 2) == 0 || ft_strncmp(str, "C", 1) == 0 || \
	ft_strncmp(str, "F", 1) == 0)
		return (1);
	return (0);
}

void	pars_map_norm_2(t_map *stock, int *j)
{
	stock->num_cols = stock->longest - 1;
	stock->only_map[*j] = NULL;
	stock->height = *j;
}	
