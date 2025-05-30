/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:10:10 by fforster          #+#    #+#             */
/*   Updated: 2025/05/13 15:49:41 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef MOVEMENT_SPEED
#  define MV_SPEED 4.0
# endif

# ifndef ROTATE_SP
#  define RT_SPEED 2.0
# endif

# ifndef S_WIDTH
// #  define S_WIDTH 960
#  define S_WIDTH 1280
// #  define S_WIDTH 1600
// #  define S_WIDTH 1920
# endif

# ifndef S_HEIGHT
// #  define S_HEIGHT 540
#  define S_HEIGHT 720
// #  define S_HEIGHT 900
// #  define S_HEIGHT 1080
# endif

# ifndef COLORS
#  define CEILING_COLOR 4278195967
#  define FLOOR_COLOR 
# endif

# ifndef MINI
#  define MINI_RESIZE_FACTOR 2
#  define MINI_UNITS_PER_TILE 10
#  define R 233
#  define G 166
#  define B 0
#  define A 255
#  define FOV 0.77
// The amount by which we shift each line (in radians)
// the smaller the more lines are drawn, which affects performance but has no 
// non set pixels
#  define ANGLE_SPREAD 0.001
#  define MINI_RAY_LENGRH 1
#  define MINI_LINE_HEIGHT 1
#  define MINI_LINE_WIDTH 2
# endif

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "colors.h"
# include "garbage_collector.h"
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// changing to double because math librarys are using double on iOS
typedef struct coordinates
{
	double	y;
	double	x;
}		t_cords;

// mlx_put_pixel needs int32
typedef struct coordinates_int32
{
	int32_t	y;
	int32_t	x;
}		t_cords_int32;

// player coords resized for minimap FOV
typedef struct miniplayer
{
	double			x;
	double			y;
}		t_miniplayer;

// minimap tile size in pixel
typedef struct height_width
{
	u_int32_t	height;
	u_int32_t	width;
}		t_height_width;

enum e_scene_dir
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
	FLOOR = 5,
	CEILING = 6,
	WC = 7,
	UNIDENTIFIED = 8
};

// holds player info like position and spawn rules
typedef struct player
{
	// exact position
	t_cords	pos;
	// direction of sight, range is -1 to 1 for x and y
	t_cords	dir;
	// saves direction N/E/S/W
	char	looking;
	bool	moving;
	bool	punch;
	bool	build;
}		t_player;

// holds info about map like size and each tiles content
typedef struct map
{
	// all tiles (this will be malloced())
	char	**tiles;
	// for parsing
	char	**copy;
	size_t	map_scene_start;
	bool	recieved_color1;
	bool	recieved_color2;
	// amount of max tiles in y and in x
	size_t	max_y;
	size_t	max_x;

	t_cords	spawn;

	int		floor_color;
	int		ceiling_color;
}		t_map;

// holds variables needed for the raycasting
typedef struct raycaster
{
	//current tile the ray is in
	size_t	tile_y;
	size_t	tile_x;

	//camera plane
	t_cords	plane;

	//x-coordinate in camera space
	double	camera_x;

	//direction of a singular (current) rayf, our eyesight
	t_cords	ray_dir;

	// length of the ray from current pos to the closest x/y wall,
	// will increase to the lenght of the shot ray using delta dist
	t_cords	side_dist;

	//length of ray from one x or y-side to next x or y-side
	t_cords	delta_dist;

	//perpandicular distance to the wall
	double	perp_wall_dist;

	bool	hit_x_wall;
	//the x point where the ray intersects with the wall
	//range: 0 - 1.0 (left - right)
	double	x_intersect;

	int		go_y;
	int		go_x;

	// draw vertical line
	// wall drawing
	int		draw_start;
	int		draw_end;
	int		wall_height;
}		t_ray;

typedef struct textures
{
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
	mlx_texture_t	*hands[7];
	mlx_texture_t	*wallcrack;
	int				*color_no;
	int				*color_so;
	int				*color_we;
	int				*color_ea;
}		t_textures;

typedef struct master_struct
{
	mlx_t			*mlx;

	mlx_image_t		*bg;
	mlx_image_t		*hands[7];
	mlx_image_t		*wallcrack;
	t_textures		textures;

	t_map			map;
	t_player		player;
	t_ray			ray;

	bool			steal_mouse;

	// pressed M then show mini
	bool			show_minimap;
	// map changed on built, crack and destroyed
	bool			changed_map;
	// when drawn and put into frame queue, do not draw again, use img->enable
	bool			minimap_drawn;
	double			mini_resize_factor;
	mlx_image_t		*minimap;
	mlx_image_t		*minifov;
	// coords end for fov cone line
	double			fov_line_end_x;
	double			fov_line_end_y;
}		t_game;

//src/error.c
void	delete_textures(t_textures *t);
void	ft_error(char *msg, int errcode, t_game	*game);
void	ft_free_dp(char **dp);
void	parse_error(t_map *map, t_textures *tex, char *msg, char **raw_scene);

//src/graphics/hands.c
void	build_wall(t_game *g);
bool	change_map_element(t_game *g, char src, char dest, char **m);
void	punch(t_game *g);
void	reset_hands(t_game *g);
void	sway_hands(t_game *g);

//src/graphic/image.c
int		get_rgba(int r, int g, int b, int a);
void	pixset_yx_height_width(mlx_image_t *img, int colour,
			t_cords_int32 xy, t_height_width height_width);

//src/graphics/lines.c
void	draw_line_to_bottom(t_game *game, double start_x,
			double start_y, double slope);
void	draw_line_to_left(t_game *game, double start_x, double start_y,
			double slope);
void	draw_line_to_right(t_game *game, double start_x, double start_y,
			double slope);
void	draw_line_to_top(t_game *game, double start_x, double start_y,
			double slope);
double	slope(double x_diff, double y_diff);

//src/graphic/minifov.c
void	clear_mini_fov_img(t_game *game, t_cords_int32 yx);
void	draw_fov_direction_line(t_game *game);
void	draw_mini_fov(t_game *game);

//src/graphic/minimap.c
void	draw_tile_on_change(t_game *game, size_t y, size_t x,
			t_height_width height_width);
void	draw_minimap_tile(t_game *game, size_t y, size_t x,
			t_height_width height_width);
void	init_minimap(t_game *game);
void	mini_img_for_resize_factor(t_game *game,
			t_height_width *height_width);
void	minimap_change(t_game *game);

//src/hooks/game_loop.c
void	draw_vertical_line(t_game *g, int i);
void	print_ray_status(t_game *g);
void	ray_len_and_hitpoint(const t_player p, t_ray *r);
void	raycaster_loop(void *param);
void	shoot_ray(t_game *g);
void	step_which_side(t_game *g);

//src/hooks/keyhook.c
void	hands_keyhook(t_game *g);
void	minimap_keyhook(t_game *g);
void	movement_keyhook(t_game *g);
void	my_keyhook(mlx_key_data_t keydata, void *param);

//src/hooks/mousehook.c
void	my_cursor(double xpos, double ypos, void *param);
void	my_mouse_button(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);

//src/hooks/move_player.c
void	walk_backwards(char **tiles, t_cords *pos, t_cords *dir,
			double mv_speed);
void	walk_forward(char **tiles, t_cords *pos, t_cords *dir, double mv_speed);
void	rotate_player(t_cords *dir, t_cords *plane, double rt_speed);
void	strafe_left(char **tiles, t_cords *pos, t_cords *dir, double mv_speed);
void	strafe_right(char **tiles, t_cords *pos, t_cords *dir, double mv_speed);

// src/hooks/vertical_line_draw.c
void	draw_pixel_from_tex(t_game *g, unsigned int x, mlx_texture_t *tex,
			int *wall_color);
void	draw_wallcrack(t_game *g, int x, int wall_height);
int		get_x_of_texture(t_game *game, uint32_t tex_width);
void	print_ray_status(t_game *g);
void	select_wall_texture(t_game *g, mlx_texture_t **tex, int **wall_color);

//src/init/init_hands.c
void	init_hands(t_game *g);

//src/init/init_ray.c
void	init_raycaster(t_game *g);

//src/main.c
int		main(int ac, char **av);

//src/parse/make_element.c
int		make_color(t_game *game, char *scene_line, int curr_col, size_t l);
int		make_texture(t_game *g, char *scene_line, int curr_element, size_t l);

//src/parse/parse_map.c
void	parse_map(t_map *map, t_player *player, t_textures *tex, char *path);

//src/parse/parse_scene.c
bool	ft_isspace(char c);
void	parse_scene(t_game *game, int ac, char **av);

//src/parse/parse_scene_utils.c
bool	check_for_errors(const char *scene_line, size_t l);
bool	ft_isspace(char c);
void	ft_skip_spaces(const char *str, size_t *index);
char	**read_scenefile(char *av);
bool	recieved_all_elements(t_game *game);

//src/textures.c
int		*create_color_array(t_game *g, mlx_texture_t *tex);
void	fill_texture_colors(t_game *game);
#endif