#include "main.h"

float normalize_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
        angle = TWO_PI + angle;
    return (angle);
}

int has_collision(t_game *game, float x, float y, char num)
{
    int map_x;
    int map_y;
    int ret;

    if (x < 0 || x >= game->map.window_width * game->map.tile_size || y < 0 || y >= game->map.window_height * game->map.tile_size)
        return (TRUE);
    map_x = x / game->map.tile_size;
    map_y = y / game->map.tile_size;
	// printf("[%d,%d]\n", map_y, map_x);
    if (game->map.my_map[map_y] && (ft_strlen(game->map.my_map[map_y]) > (size_t)map_x && (size_t)map_x >= 0) && game->map.my_map[map_y][map_x] && game->map.my_map[map_y][map_x] == num)
        ret = TRUE;
    else
        ret = FALSE;
    return (ret);
}

int wall_collection(t_game *game, float x, float y, char num)
{
	float map_x;
	float map_y;

	map_x = x / game->map.tile_size;
	map_y = y / game->map.tile_size;
	if (game->map.my_map[(int)(map_y + 0.2)][(int)(map_x)] == num)
		return(TRUE);
	if (game->map.my_map[(int)(map_y - 0.2)][(int)(map_x)] == num)
		return(TRUE);
	if (game->map.my_map[(int)(map_y)][(int)(map_x + 0.2)] == num)
		return(TRUE);
	if (game->map.my_map[(int)(map_y)][(int)(map_x - 0.2)] == num)
		return(TRUE);
	return (FALSE);
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
    if (!has_collision(game, newPlayerX, newPlayerY, '1') && !wall_collection(game, newPlayerX, newPlayerY, '1'))
    {
        game->player.x = newPlayerX;
        game->player.y = newPlayerY;
    }
    newPlayerX = game->player.x + cos(game->player.rotationAngle + 0.5 * PI) * side_step;
    newPlayerY = game->player.y + sin(game->player. rotationAngle + 0.5 * PI) * side_step;
    if (!has_collision(game, newPlayerX, newPlayerY, '1') && !wall_collection(game, newPlayerX, newPlayerY, '1'))
    {
        game->player.x = newPlayerX;
        game->player.y = newPlayerY;
    }
}