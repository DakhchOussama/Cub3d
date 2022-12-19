#include "main.h"

void playerPosition(t_player *player, t_map map)
{
    int i;
    int j;

    i = 0;
    while (i < map.height)
    {
        j = 0;
        while (j < map.num_cols)
        {
            if (map.my_map[i][j] == 'N' || map.my_map[i][j] == 'S' || map.my_map[i][j] == 'E' || map.my_map[i][j] == 'W')
            {
                player->x = j * map.tile_size + (map.tile_size / 2);
                player->y = i * map.tile_size + (map.tile_size / 2);
            }
            j++;
        }
        i++;
    }
}