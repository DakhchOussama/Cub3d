#include "main.h"

int row_length(char **table)
{
    int i;
	int compt;

    i = 5;
	compt = 1;
    while(table[i])
	{
		compt++;
        i++;
	}
    return (compt);
}

void setup(t_player *player, t_map map)
{
    // initialize and setup game objects
    playerPosition(player, map);
    player->width = 1;
    player->height = 1;
    player->turnDirection = 0;
    player->walkDirection = 0;
	player->walkDirection_side = 0;
    player->rotationAngle = 1.5 * PI; // pi / 2
    player->walkSpeed = 60;
    player->turnSpeed = 30 * (PI / 180);
}

int row_length_file(char **table)
{
	int i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

void takeSize(char **table , t_map *map)
{
    int i;

    i = 0;
    map->num_rows = row_length(table);
	map->num_rows_file = row_length_file(table);
    if (map->num_rows == 0)
        display_error("free Map");
    map->num_cols = ft_strlen(table[5]);
    map->tile_size = 60; //????
    map->window_height = map->num_rows * map->tile_size; // 780
    map->window_width = map->num_cols * map->tile_size; // 1200
}

void put_text(char **line, int num, t_map *map)
{
	int i;
	int length;

	length = ft_strlen(line[num]);
	i = 0;
	while (i < length)
	{
		if (line[num][i] == ' ')
		{
			i++;
			if (num == 0)
				map->NO = ft_substr(line[num], i, length);
			else if (num == 1)
				map->SO = ft_substr(line[num], i, length);
			else if (num == 2)
				map->WE = ft_substr(line[num], i, length);
			else if (num == 3)
				map->EA = ft_substr(line[num], i, length);
		}
		i++;
	}
}

void verify_data(char **line, t_map *map)
{
	if (ft_strncmp(line[0], "NO", 2) == 0)
		put_text(line, 0, map);
	if (ft_strncmp(line[1], "SO", 2) == 0 )
		put_text(line, 1, map);
	if (ft_strncmp(line[2], "WE", 2) == 0)
		put_text(line, 2, map);
	if (ft_strncmp(line[3], "EA", 2) == 0)
		put_text(line, 3, map);
}

void fillMap(char *line, char *buff, t_map *map)
{
    int i;

    i = 0;
    while (line[i] && i < map->num_cols)
    {
        if (line[i] == '0')
            buff[i] = '0';
        else if (line[i] == '1')
            buff[i] = '1';
        else if (line[i] == '2')
            buff[i] = '2';
        else if (line[i] == 'N')
			buff[i] = 'N';
		// else
        //     display_error("Parsing Error\n");
        i++;
    }
}

// void free_map(char **map_tab)
// {
// 	int i;

// 	i = 0;
// 	while (map_tab[i])
// 	{
// 		free(map_tab[i]);
// 		i++;
// 	}
// }

void    setup_map(t_map *map, char *table)
{
    char **str;
    char **map_tab;
    int i;
	int j;

    str = ft_split(table, '\n');
    if (!str)
        display_error("Error in Map");
	verify_data(str, map);
    takeSize(str, map);
    map_tab = (char **)malloc((map->num_rows) * sizeof(char *));
    if (!map_tab)
        display_error("Map Allocation error\n");
    map_tab[map->num_rows] = NULL;
    i = 4;
	j = 0;
    while (i < map->num_rows_file && j < map->num_rows)
    {
        map_tab[j] = (char *) malloc((map->num_cols) * sizeof(char));
        if (!map_tab[j])
            display_error("Map allocation error\n");
        fillMap(str[i], map_tab[j], map);
		j++;
        i++;
    }
	map->my_map = map_tab; //????
	// free_map(map_tab);
}


