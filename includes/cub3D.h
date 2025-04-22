/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:10:10 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 14:51:19 by nsloniow         ###   ########.fr       */
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
// #  define MINI_RESIZE_FACTOR 2
#  define MINI_UNITS_PER_TILE 10
// #  define R 111
// #  define G 11
// #  define B 11
// #  define A 255
#  define R 233
#  define G 166
#  define B 0
#  define A 255
#  define FOV 0.77
// The amount by which we shift each line (in radians)
// the smaller the more lines are drawn, which affects performance but has no 
// non set pixels
#  define ANGLE_SPREAD 0.001
// #  define Lines_FOR_CONE 50
#  define MINI_RAY_LENGRH 1
#  define MINI_LINE_HEIGHT 1
#  define MINI_LINE_WIDTH 2
# endif

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "garbage_collector.h"
# include "colors.h"
# include "../MLX42/include/MLX42/MLX42.h"

enum e_scene_dir
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
	FLOOR = 5,
	CEILING = 6,
	UNIDENTIFIED = 7
};

// changing to double because math librarys are using double on iOS
typedef struct coordinates
{
	double	y;
	double	x;

}		t_cords;

typedef struct coordinates_int32
{
	int32_t	y;
	int32_t	x;
}		t_cords_int32;

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
	bool	look_x_wall;
}		t_player;

typedef struct height_width
{
	u_int32_t	height;
	u_int32_t	width;
}				t_height_width;

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

}		t_ray;

typedef struct textures
{
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
	mlx_texture_t	*hands[4];
	mlx_texture_t	*wallcrack;
	int				*color_no;
	int				*color_so;
	int				*color_we;
	int				*color_ea;
}					t_textures;

typedef struct master_struct
{
	mlx_t			*mlx;

	mlx_image_t		*bg;
	mlx_image_t		*hands[4];
	mlx_image_t		*wallcrack;
	t_textures		textures;

	t_map			map;
	t_player		player;
	t_ray			ray;

	bool			steal_mouse;

	bool			show_minimap;
	bool			changed_map;
	bool			minimap_drawn;
	double			mini_resize_factor;
	mlx_image_t		*minimap;
	int				*mini_color;
	mlx_image_t		*minifov;
	double			fov_line_end_x;
	double			fov_line_end_y;
	mlx_image_t		*img;
}					t_game;

// //src/main.c
// int		get_rgba(int r, int g, int b, int a);

//src/parse/parse_scene.c
void	parse_scene(t_game *game, int ac, char **av);
char	**read_scenefile(char *av);
bool	ft_isspace(char c);

//src/parse/parse_map.c
void	parse_map(t_map *map, t_player *player, t_textures *tex, char *path);

//src/init/init_ray.c
void	init_raycaster(t_game *g);
//src/error.c
void	ft_error(char *msg, int errcode, t_game	*game);
void	parse_error(t_map *map, t_textures *tex, char *msg, char **raw_scene);
void	ft_free_dp(char **dp);
void	delete_textures(t_textures *t);

//src/graphic/minimap.c
void	clear_img(mlx_image_t *img);
void	draw_fov_direction_line(t_game *game);
void	draw_mini_fov(t_game *game);
void	init_minimap(t_game *game);
void	save_pixels_for_reinstate(t_game *game);
void	minimap_change(t_game *game);

//src/hooks/game_loop.c
void	raycaster_loop(void *param);
void	step_which_side(t_game *g);
void	shoot_ray(t_game *g);
void	ray_len_and_hitpoint(const t_player p, t_ray *r);
void	draw_vertical_line(t_game *g, int i);
void	print_ray_status(t_game *g);

//src/hooks/keyhook.c
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	movement_keyhook(t_game *g);
void	my_mouse_button(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);
void	my_cursor(double xpos, double ypos, void *param);

//src/textures.c
int		*create_color_array(t_game *g, mlx_texture_t *tex);
void	fill_texture_colors(t_game *game);

//src/graphic/image.c
unsigned int	get_rgba(int r, int g, int b, int a);
void			pixset(mlx_image_t *img, int colour);
void			pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
				t_height_width height_width);

//src/graphics/hands.c
void	draw_hands(t_game *g);
bool	change_map_element(t_game *g, char src, char dest);
void	punch(t_game *g);
void	sway_hands(t_game *g);


#endif