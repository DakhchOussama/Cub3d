#include "main.h"

void draw_mini_map(t_data data, int cmp1, int cmp2, int tileColor)
{
    int i;
    int j;

    i = cmp1;
    while (i < cmp1 + 60)
    {
        j = cmp2;
        while (j < cmp2 + 60)
        {
            my_mlx_pixel_put(&data, i, j, tileColor);
            j++;
        }
        i++;
    }
}

void draw_line(t_data data, t_player *player)
{
    double bx;
    double by;
    int dx;
    int dy;
    double xn;
    double yn;
    double X;
    double Y;
    int i;
    double m;

    bx = player->x + sin(player->rotationAngle) * 50;
    by = player->y + cos(player->rotationAngle) * 50;
    dx = bx - player->x;
    dy = by - player->y;

    if (abs(dx) >= abs(dy))
        m = abs(dx);
    else
        m = abs(dy);
    xn = dx / m;
    yn = dy / m;

    X = player->x;
    Y = player->y;
    i = 0;
    while (i < m)
    {
        my_mlx_pixel_put(&data, X, Y, 0x000000);
        X = X + xn;
        Y = Y + yn;
        i++;
    }
}

void playerPosition(t_player *player, t_map map)
{
    int i;
    int j;

    i = 0;
    while (i < map.num_rows)
    {
        j = 0;
        while (j < map.num_cols)
        {
            if (map.my_map[i][j] == 'N')
            {
                player->x = j * map.tile_size;
                player->y = i * map.tile_size;
            }
            j++;
        }
        i++;
    }
}

void draw_player(t_data data, t_player *player)
{
    int i;
    int j;

    i = player->x;
    while (i < player->x + 1)
    {
        j = player->y;
        while (j < player->y + 1)
        {
            my_mlx_pixel_put(&data, i, j, 0x00000);
            j++;
        }
        i++;
    }
}