/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:01:10 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/24 16:45:49 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting/main.h"

void	verify_place(char c, t_map *map)
{
	if (c == 'N')
		map->position = 'N';
	else if (c == 'S')
		map->position = 'S';
	else if (c == 'E')
		map->position = 'E';
	if (c == 'W')
		map->position = 'W';
}

int	stock_texturs(t_map *text, char **spl)
{
	if (!ft_strcmp(spl[0], "NO") && text->no == NULL)
		text->no = ft_strdup(spl[1]);
	else if (!ft_strcmp(spl[0], "NO") && text->no)
		return (printf("Error:\nduplicated\n"), free_2d(spl), exit(1), -1);
	if (!ft_strcmp(spl[0], "SO") && text->so == NULL)
		text->so = ft_strdup(spl[1]);
	else if (!ft_strcmp(spl[0], "SO") && text->so)
		return (printf("Error:\nduplicated\n"), free_2d(spl), exit(1), -1);
	if (!ft_strcmp(spl[0], "WE") && text->we == NULL)
		text->we = ft_strdup(spl[1]);
	else if (!ft_strcmp(spl[0], "WE") && text->we)
		return (printf("Error:\nduplicated\n"), free_2d(spl), exit(1), -1);
	if (!ft_strcmp(spl[0], "EA") && text->ea == NULL)
		text->ea = ft_strdup(spl[1]);
	else if (!ft_strcmp(spl[0], "EA") && text->ea)
		return (printf("Error:\nduplicated\n"), free_2d(spl), exit(1), -1);
	return (1);
}

int	check_texture_norm(t_map *text, char **spl)
{
	if (spl[0] && !(ft_strcmp(spl[0], "NO") && ft_strcmp(spl[0], "SO") \
	&& ft_strcmp(spl[0], "WE") && ft_strcmp(spl[0], "EA")))
	{
		if (spl[1] && !spl[2] && !ft_strncmp((spl[1] + \
			ft_strlen(spl[1]) - 4), ".xpm", 4))
			stock_texturs(text, spl);
		else if (spl[2])
			return (printf("Error:\nin map"), free_2d(spl), exit(1), 1);
		else
			return (printf("Error:\nfile is not extension '.xpm'"), \
				free_2d(spl), exit(1), 1);
	}
	return (0);
}

void	*check_c_and_f(t_map *text, char *map)
{
	char	**spl;

	spl = ft_spl(map, ", \t\n\v\r");
	if (!spl)
		exit(1);
	if (spl[4])
		return (printf("Error:\nin map"), free_2d(spl), exit(1), NULL);
	if (spl[0] && !(ft_strcmp(spl[0], "F") && ft_strcmp(spl[0], "C")))
		line_c_and_f(spl, map);
	if (!ft_strcmp(spl[0], "C") && !text->c)
		text->c = (ft_atoi(spl[1]) << 16) + \
		(ft_atoi(spl[2]) << 8) + (ft_atoi(spl[3]));
	else if (!ft_strcmp(spl[0], "C") && text->c)
		return (printf("Error:\nduplicate C color"), \
		free_2d(spl), exit(1), NULL);
	else if (!ft_strcmp(spl[0], "F") && !text->f)
		text->f = (ft_atoi(spl[1]) << 16) + \
		(ft_atoi(spl[2]) << 8) + (ft_atoi(spl[3]));
	else if (!ft_strcmp(spl[0], "F") && text->f)
		return (printf("Error:\nduplicate F color"), \
		free_2d(spl), exit(1), NULL);
	free_2d(spl);
	return (NULL);
}

int	check_texture(t_map *text, char *map)
{
	int		i;
	char	**spl;

	i = 0;
	if (map[i] == '\n')
		return (0);
	while (map[i] && (map[i] == ' ' || map[i] == '\t'))
		i++;
	if (map[i] && (map[i] == '0' || map[i] == '1'))
		return (first_and_last(text), 1);
	spl = ft_spl(map, " \n\t\v\r");
	if (!spl)
		return (exit(1), 1);
	if (ft_strlen(spl[0]) == 2 && text->my_map[0][0] != '1' \
		&& text->my_map[0][0] != '0')
		check_texture_norm(text, spl);
	else if (text->my_map[0][0] != '0' \
		&& text->my_map[0][0] != '1')
		check_c_and_f(text, map);
	free_2d(spl);
	return (0);
}
