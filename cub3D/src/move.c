#include "main.h"

float normalize_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
    {
        angle = TWO_PI + angle;
    }
    return (angle);
}

int has_collision(t_game *game, float x, float y, int num)
{
    int map_x;
    int map_y;
    int ret;

    if (x < 0 || x >= game->map.window_width * game->map.tile_size || y < 0 || y >= game->map.window_height * game->map.tile_size)
        return (TRUE);
    map_x = x / game->map.tile_size;
    map_y = y / game->map.tile_size;
    if (game->map.my_map[map_y][map_x] == num)
        ret = TRUE;
    else
        ret = FALSE;
    return (ret);
}

void move(t_game *game)
{
    float moveStep;
    float side_step;
    float newPlayerX;
    float newPlayerY;

    game->player.rotationAngle += game->player.turnDirection * game->player.turnSpeed;
    game->player.rotationAngle = normalize_angle(game->player.rotationAngle);
    moveStep = game->player.walkDirection * game->player.walkSpeed;
    side_step = game->player.walkDirection_side * game->player.walkSpeed;
    newPlayerX = game->player.x + cos(game->player.rotationAngle) * moveStep;
    newPlayerY = game->player.y + sin(game->player.rotationAngle) * moveStep;
    if (!has_collision(game, newPlayerX, newPlayerY, '1') && !has_collision(game, newPlayerX, newPlayerY, '2'))
    {
        game->player.x = newPlayerX;
        game->player.y = newPlayerY;
    }
    newPlayerX = game->player.x + cos(game->player.rotationAngle + 0.5 * PI) * side_step;
    newPlayerY = game->player.y + sin(game->player.rotationAngle + 0.5 * PI) * side_step;
    if (!has_collision(game, newPlayerX, newPlayerY, '1') && !has_collision(game, newPlayerX, newPlayerY, '2'))
    {
        game->player.x = newPlayerX;
        game->player.y = newPlayerY;
    }
}

// void move_left(t_game *game)
// {
//     float moveStep;
//     float newPlayerX;

//     game->player.turnDirection = -1;
//     moveStep = game->player.walkSpeed * game->player.turnDirection;
//     newPlayerX = game->player.x + moveStep;
//     if (isTherWallLeft(game))
//         return ;
//     game->player.x = newPlayerX;
//     render(game);
//     // game->player.turnDirection = 0;
// }

// void move_up(t_game *game)
// {
//     float moveStep;
//     float newPlayerY;

//     game->player.walkDirection = -1;
//     moveStep = game->player.walkDirection * game->player.walkSpeed;
//     newPlayerY = game->player.y + moveStep;
//     if (isTherWallUp(game))
//         return ;
//     game->player.y = newPlayerY;
//     render(game);
//     // game->player.walkDirection = 0;
// }

// void move_down(t_game *game)
// {
//     float moveStep;
//     float newPlayerY;

//     game->player.walkDirection = +1;
//     moveStep = game->player.walkDirection * game->player.walkSpeed;
//     newPlayerY = game->player.y + moveStep;
//     if (isTherWallDown(game))
//         return ;
//     game->player.y = newPlayerY;
//     render(game);
//     // game->player.walkDirection = 0;
// }

// void move_rotation_left(t_game *game)
// {
//     game->player.turnDirection = +1;
//     game->player.rotationAngle += game->player.turnDirection * game->player.turnSpeed * 0.5;
//     render(game);
//     // game->player.turnDirection = 0;
// }

// void move_rotation_right(t_game *game)
// {
//     game->player.turnDirection = -1;
//     game->player.rotationAngle += game->player.turnDirection * game->player.turnSpeed * 0.5;//FPS
//     render(game);
//     game->player.turnDirection = 0;
// }