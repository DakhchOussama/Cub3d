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

void playerPosition(t_player *player, t_map map)
{
    player->x = map.stock_j * map.tile_size + (map.tile_size / 2);
    player->y = map.stock_i * map.tile_size + (map.tile_size / 2);
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
	if (map.position == 'N')
		player->rotationAngle = 1.5 * PI;
	else if (map.position == 'S')
    	player->rotationAngle = 0.5 * PI;
	else if (map.position == 'E')
    	player->rotationAngle = 0;
	else if (map.position == 'W')
    	player->rotationAngle = PI;
    player->walkSpeed = 60;
    player->turnSpeed = 5 * (PI / 180);
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
    map->height = row_length(table);
	map->len = row_length_file(table);
    if (map->height == 0)
        display_error("free Map");
    map->num_cols = ft_strlen(table[5]);
    map->tile_size = 60;
    map->window_height = map->height * map->tile_size; // 780
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
		{
			map->position = 'N';
			buff[i] = 'N';
		}
		else if (line[i] == 'S')
		{
			map->position = 'S';
			buff[i] = 'S';
		}
		else if (line[i] == 'E')
		{
			map->position = 'E';
			buff[i] = 'E';
		}
		else if (line[i] == 'W')
		{
			map->position = 'W';
			buff[i] = 'W';
		}
		// else
        //     display_error("Parsing Error\n");
        i++;
    }
}

void    setup_map(t_map *map, char *table)
{
    char **str;
    int i;
	int j;

    str = ft_split(table, '\n');
    if (!str)
        display_error("Error in Map");
	verify_data(str, map);
    takeSize(str, map);
    map->my_map = (char **)malloc((map->height) * sizeof(char *));
    if (!map->my_map)
        display_error("Map Allocation error\n");
    map->my_map[map->height] = NULL;
    i = 4;
	j = 0;
    while (i < map->len && j < map->height)
    {
        map->my_map[j] = (char *) malloc((map->num_cols) * sizeof(char));
        if (!map->my_map[j])
            display_error("Map allocation error\n");
        fillMap(str[i], map->my_map[j], map);
		j++;
        i++;
    }
}


