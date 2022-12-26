/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:02:04 by odakhch           #+#    #+#             */
/*   Updated: 2022/12/26 23:14:40 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>
# include "../libft/libft.h"
# include "../parsing/get_next_line/get_next_line.h"

# define TRUE 1
# define FALSE 0
# define PI 3.14159265359
# define TWO_PI 6.28318530718
# define FOV 1.0472

typedef struct s_data
{
	void	*mlx;
	void	*img;
	char	*addr;
	void	*window;
	int		bpp;
	int		zl;
	int		ed;
	int		width;
	int		height;
}			t_data;

typedef struct s_map
{
	int		c;
	int		f;
	int		only_map_len;
	int		len;
	char	**my_map;
	char	**only_map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		height;
	int		window_width;
	int		window_height;
	char	position;
	int		tile_size;
	int		num_cols;
	int		stock_i;
	int		stock_j;
	size_t	longest;
}			t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	int		walk_direction_side;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}			t_player;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		ray_facing_up;
	int		ray_facing_down;
	int		ray_facing_left;
	int		ray_facing_right;
	int		found_wall_hit;
	float	next_touch_x;
	float	next_touch_y;
	int		ray_up;
	int		ray_down;
	int		ray_left;
	int		ray_right;
	float	xtocheck;
	float	ytocheck;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	int		wall_content;
}			t_ray;

typedef struct s_pic
{
	int		i;
	int		j;
	int		x;
	int		y;
	float	width;
	float	height;
	float	distanceprojplan;
	float	correct_distance;
	float	projection_wall;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		distance_from_top;
	int		textoffset_x;
	int		textoffset_y;
	int		color;
}			t_pic;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		size;
	int		bpp;
	int		zl;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_text
{
	t_data	north;
	t_data	south;
	t_data	west;
	t_data	east;
	t_data	now;
	int		textur[8];
}			t_text;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_data		data;
	t_ray		raycast;
	t_ray		horizantal;
	t_ray		vertical;
	t_ray		*ray;
	t_pic		pic;
	t_img		img;
	t_text		text;
}	t_game;

//free function
void	exit_game(t_game *game);
int		ft_cross(t_game *game);
void	free_mlx(t_game *game);
void	display_error(char *msg);
void	free_check(char *str);
//draw & create window
void	createwindow(t_data *mlx, t_map map);
void	setup(t_player *player, t_map map);
void	processInput(t_data data);
void	render(t_game *game);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		my_mlx_pixel_pick(t_data *data, int x, int y);
void	process_input(t_game *game);
int		direction(int keyboard, t_game *game);
//move player
void	moveplayer(t_game *game, int *direction, int num);
void	move(t_game *game);
void	player_position(t_player *player, t_map map);
void	check_right_left(t_game *game);
void	takeSize(char **table, t_map *map);
int		key_press(int keyboard, t_game *game);
int		key_release(int keyboard, t_game *game);
int		wall_collection(t_game *game, float x, float y, char num);
void	map_3d(t_game *game);
void	put_pixel(t_game *game, t_pic *pic, int wallStrpHeight);
int		found_wall_strip_height(t_pic *pic, t_game *game);
//ray-cast
float	normalize_angle(float angle);
void	castray(float rayAngle, int id, t_game *game);
void	castallrays(t_game *game);
void	setup_rays(t_ray *raycast);
float	distance_between_points(float x, float y, float x2, float y2);
void	horizontal_intersection(t_game *game, float ray_angle);
void	horizontal_intersection2(t_game *game, int max_width, int max_height);
void	vertical_intersection2(t_game *game, int max_width, int max_height);
void	vertical_intersection(t_game *game, float ray_angle);
int		has_collision(t_game *game, float x, float y, char num);
void	verify_lower_intersection(t_game *game, float rayAngle, int id);
void	put_on_struct(t_ray *ray, t_game *game, int id, int choose);
void	allocate_rays(t_game *game);
void	check_ray(t_game *game);
//texture
void	put_textures_in_array(t_text *text);
int		setup_texture(t_game *game, t_text *text);
void	chose_tile_size(t_game *game, t_text *text);

//parsing
int		check_extention(char *av);
int		ft_parsing(t_map *pars, char **av);
char	**ft_spl(char *str, char *spl);
int		ft_parsing_frist(t_game *game, int ac, char **av);
void	free_2d(char **tab);
void	*pars_map(t_map *stock, char **av);
int		ft_error_fd(int fd);
int		check_extention(char *av);
void	init(t_map *texturs);
void	*first_and_last(t_map *my_map);
void	verify_place(char c, t_map *map);
int		check_texture(t_map *text, char *map);
int		stock_texturs(t_map *text, char **spl);
void	*check_c_and_f(t_map *text, char *map);
void	init(t_map *texturs);
void	*line_c_and_f(char **spl, char *map);
int		ft_strsearch(char *str);
void	pars_map_norm(t_map *stock, int i, char **av);
void	pars_map_norm_2(t_map *stock, int *j);
int		pars_map_norm_again(char *str);

#endif
