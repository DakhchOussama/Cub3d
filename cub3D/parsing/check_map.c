/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 00:42:02 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/17 00:07:44 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <stdio.h>
#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
# include "../libft/libft.h"
#include "get_next_line/get_next_line.h"

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

void	init(t_pars *texturs)
{
	texturs->NO = NULL;
	texturs->SO = NULL;
	texturs->WE = NULL;
	texturs->EA = NULL;
	texturs->C = 0;
	texturs->F = 0;
	texturs->only_map_len = 0;
}

int stock_texturs(t_pars *text, char **spl)
{
	if (!ft_strcmp(spl[0], "NO") && text->NO == NULL)
		text->NO = spl[1];
	else if (!ft_strcmp(spl[0], "NO") && text->NO)
		return (printf("Error:\nduplicated\n"), free_2d(spl), exit(1), -1);
	if (!ft_strcmp(spl[0], "SO") && text->SO == NULL)
		text->SO = spl[1];
	else if (!ft_strcmp(spl[0], "SO") && text->SO)
		return (printf("Error:\nduplicated\n"), free_2d(spl), exit(1), -1);
	if (!ft_strcmp(spl[0], "WE") && text->WE == NULL)
		text->WE = spl[1];
	else if (!ft_strcmp(spl[0], "WE") && text->WE)
		return (printf("Error:\nduplicated\n"), free_2d(spl), exit(1), -1);
	if (!ft_strcmp(spl[0], "EA") && text->EA == NULL)
		text->EA = spl[1];
	else if (!ft_strcmp(spl[0], "EA") && text->EA)
		return (printf("Error:\nduplicated\n"), free_2d(spl), exit(1), -1);
	return (1);
}

int	ft_strsearch(char *str)
{
	int	i;
	int ver;

	ver = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			ver++;
		if(str[i + 1] && str[i] == ',' && str[i + 1] == ',')
			return (1);
		i++;
	}
	if(ver != 2)
		return (1);
	return (0);
}

void	*line_C_and_F(t_pars *text, char **spl, char *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (++i <= 3)
		if (ft_atoi(spl[i]) < 0 || ft_atoi(spl[i]) > 255)
			return (printf("Error\nR.G.B values"), free_2d(spl), exit(1), NULL);
	if (ft_strsearch(map))
		return (printf("Error\nR.G.B sytax"), free_2d(spl), exit(1), NULL);
	return (NULL);
}

void	*check_C_and_F(t_pars *text, char *map)
{
	char **spl;

	spl = ft_spl(map, ", \t\n\v\r");
	if (!spl)
		exit(1);
	if (spl[4])
		return (printf("Error:\nin map"), free_2d(spl), exit(1), NULL);
	if (spl[0] && !(ft_strcmp(spl[0], "F") && ft_strcmp(spl[0], "C")))
		line_C_and_F(text, spl, map);
	if (!ft_strcmp(spl[0], "C") && !text->C)
		text->C = (ft_atoi(spl[1]) << 16) + \
		(ft_atoi(spl[2]) << 8) + (ft_atoi(spl[3]));
	else if (!ft_strcmp(spl[0], "C") && text->C)
		return (printf("Error:\nduplicate C color"), free_2d(spl), exit(1), NULL);
	else if (!ft_strcmp(spl[0], "F") && !text->F)
		text->F = (ft_atoi(spl[1]) << 16) + \
		(ft_atoi(spl[2]) << 8) + (ft_atoi(spl[3]));
	else if (!ft_strcmp(spl[0], "F") && text->F)
		return (printf("Error:\nduplicate F color"), free_2d(spl), exit(1), NULL);
	free_2d(spl);
	return (NULL);
}

int	check_middle_lines_norm(t_pars *my_map, int *i, int *j)
{
	if (my_map->only_map[*i][*j] != ' ' && my_map->only_map[*i][*j] != '1')
	{
		if (my_map->only_map[*i][*j - 1] == ' ' || \
			my_map->only_map[*i][*j + 1] == ' ')
			return (printf("Error\nmap not closed"), \
				free_2d(my_map->only_map), exit(1), 1);
		if (ft_strlen(my_map->only_map[*i - 1]) - 1 <= *j || \
			ft_strlen(my_map->only_map[*i + 1]) - 1 <= *j)
			return (printf("Error\nmap not closed"), \
				free_2d(my_map->only_map), exit(1), 1);
		else if (my_map->only_map[*i - 1][*j] == ' ' || \
			my_map->only_map[*i + 1][*j] == ' ')
			return (printf("Error\nmap not closed"), \
				free_2d(my_map->only_map), exit(1), 1);
	}
	return (0);
}

void	*check_middle_lines(t_pars *my_map, int nbr)
{
	int	i;
	int	j;
	
	i = -1;
	while (my_map->only_map[++i])
	{
		j = 0;
		while (my_map->only_map[i][j] && my_map->only_map[i][j] != '\n')
		{
			if (my_map->only_map[i][j] == 'N' || my_map->only_map[i][j] == 'S' || \
				my_map->only_map[i][j] == 'E' || my_map->only_map[i][j] == 'W')
				nbr++;
			check_middle_lines_norm(my_map, &i, &j);
			j++;
		}
	}
	if (nbr != 1)
		return (printf("Error\nnbr of players"), \
			free_2d(my_map->only_map), exit(1), NULL);
	return (NULL);
}

void	*first_and_last(t_pars *my_map)
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
	check_middle_lines(my_map, 0);
	return (NULL);
}

int	pars_map_norm_again(char *str)
{
	if (ft_strncmp(str, "\n", 1) == 0 || ft_strncmp(str, "NO", 2) == 0 || 
	ft_strncmp(str, "SO", 2) == 0 || ft_strncmp(str, "WE", 2) == 0 ||
	ft_strncmp(str, "EA", 2) == 0 || ft_strncmp(str, "C", 1) == 0 || 
	ft_strncmp(str, "F", 1) == 0 )
		return (1);
	return (0);
}

int	ft_error_fd(int fd)
{
	if (0 > fd)
		return (printf("Error\n file discriptor"), exit(1), 1);
	return (0);
}

void	*pars_Map_norm(t_pars *stock, int i, char **av)
{
	int		fd;
	int		j;
	char	*str;

	j = 0;
	fd = open(av[1], O_RDWR);
	ft_error_fd(fd);
	while (i <= stock->only_map_len )
	{
		str = get_next_line(fd);
		if (str == NULL)
			break;
		if(pars_map_norm_again(str) == 1)
		{
			i++;
			free(str);
			continue;
		}
		stock->only_map[j] = str;
		i++;
		j++;
	}
	stock->only_map[j] = NULL;
	stock->height = j;
	return (NULL);
}

void	*pars_Map(t_pars *stock, char **av)
{
	int		fd;
	char	*line;
	char	*str;

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
	pars_Map_norm(stock, 0, av);
	// int k = 0;////////////////////////
	// while (stock->only_map[k] != NULL)
	// {
	// 	printf("%s",stock->only_map[k]);
	// 	k++;
	// }
	return (NULL);
}

int	check_texture_norm(t_pars *text, char **spl)
{
	if (spl[0]  && !(ft_strcmp(spl[0], "NO") && ft_strcmp(spl[0], "SO") \
	&& ft_strcmp(spl[0], "WE") && ft_strcmp(spl[0], "EA")))
	{
		if(spl[1] && !spl[2] && !ft_strncmp((spl[1] + \
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

int	check_texture(t_pars *text, char *map, char **av)
{
	char **spl;
	int i;

	i = 0;
	while (map[i] && (map[i] == ' ' || map[i] == '\t'))
		i++;
	if (map[i] && (map[i] == '0' || map[i] == '1'))
		return (first_and_last(text), 1);
	spl = ft_spl(map, " \n\t\v\r");
	if (!spl)
		return (exit(1), 1);
	if (ft_strleen(spl[0]) == 2 && text->map[0][0] != '1' \
		&& text->map[0][0] != '0')
		check_texture_norm(text, spl);
	else if (ft_strleen(spl[0]) == 1 && text->map[0][0] != '0' \
		&& text->map[0][0] != '1')
		check_C_and_F(text, map);
	free_2d(spl);
	return (0);
}

int	ft_parsing(t_pars *pars, char **av)
{
	int		fd;
	char	*line;
	int		i;
	int		res;

	i = 0;
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
	pars->map = (char **)malloc(sizeof(char *) * (pars->len + 1));
	if (!pars->map)
		return (printf("Error:\nmap is not allocated\n"), 1);
	fd = open(av[1], O_RDWR);
	ft_error_fd(fd);
	while (i + 1 < pars->len)
	{
		pars->map[i] = get_next_line(fd);
		i++;
	}
	pars->map[i] = NULL;
	i = -1;
	init(pars);
	int j = 0;
	while (pars->map[++i])
	{
		j = 0;
		while( (pars->map[i][j] == ' ' || pars->map[i][j] == '\t'))
				j++;
		if (pars->map[i][j] == '1' || pars->map[i][j] == '0')
			break;
	}
	pars_Map(pars, av);
	i = -1;
	while (pars->map[++i])
		check_texture(pars, pars->map[i], av);
	return(0);
}

int	main(int ac, char **av)
{
	int		fd;
	t_pars	pars;

	if (ac != 2)
		return (printf("Error\nCheking the arguments"), 1);
	fd = open(av[1], O_RDWR);
	ft_error_fd(fd);
	close(fd);
	if (check_extention(av[1]))
		display_error("Error\nExtention");
	if (ft_parsing(&pars, av))
		return (1);
	free_2d(pars.map);
	free_2d(pars.only_map);
	// puts("\nout--->");
	return (0);
}
