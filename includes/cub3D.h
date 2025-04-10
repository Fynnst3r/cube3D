/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:10:10 by fforster          #+#    #+#             */
/*   Updated: 2025/04/10 09:40:36 by nsloniow         ###   ########.fr       */
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
#  define S_WIDTH 1600
# endif

# ifndef S_HEIGHT
// #  define S_HEIGHT 540
#  define S_HEIGHT 900
# endif

# ifndef COLORS
#  define CEILING_COLOR 4278195967
#  define FLOOR_COLOR 
# endif

# ifndef MINI
#  define MINI_RESIZE_FACTOR 2
#  define MINI_UNITS_PER_TILE 10
#  define R 111
#  define G 11
#  define B 11
#  define A 255
#  define FOV 0.77
// The amount by which we shift each line (in radians)
#  define ANGLE_SPREAD 0.01
// #  define Lines_FOR_CONE 50
#  define MINI_RAY_LENGRH 1
#  define MINI_LINE_HEIGHT 1
#  define MINI_LINE_WIDTH 1
# endif

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "garbage_collector.h"
# include "colors.h"
# include "../MLX42/include/MLX42/MLX42.h"

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

	size_t	max_y;
	size_t	max_x;
	t_cords	spawn;

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
	mlx_texture_t	*walltex;
	int				*wallcolors;

}					t_textures;

typedef struct master_struct
{
	mlx_t			*mlx;

	mlx_image_t		*bg;
	mlx_image_t		*img;
	mlx_image_t		*wall;
	// t_textures		textures;
	t_textures		textures[5];

	t_map			map;
	t_player		player;
	t_ray			ray;

	bool			show_minimap;
	mlx_image_t		*minimap;
	double			fov_line_end_x;
	double			fov_line_end_y;
}					t_game;

//src/main.c
int		get_rgba(int r, int g, int b, int a);

//src/error.c
void	ft_error(char *msg, int errcode, t_game	*game);
// void	delete_textures(t_game *a);

//src/graphic/minimap.c
void	draw_fov_direction_line(t_game *game);
void	draw_mini_fov(t_game *game);
void	draw_mini_map(t_game *game);

//src/hooks/game_loop.c
void	raycaster_loop(void *param);
void	step_which_side(t_game *g);
void	shoot_ray(t_game *g);
void	ray_len_and_hitpoint(const t_player p, t_ray *r);
void	draw_vertical_line(t_game *g, int i);
void	print_ray_status(t_game *g);

//src/graphic/image.c
void	ft_mlx_draw_pixel(uint8_t *pixel, uint32_t color);
void	ft_mlx_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
			uint32_t color);
int		get_rgba(int r, int g, int b, int a);
void	pixset(mlx_image_t *img, int colour);
void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
			t_height_width height_width);

//src/hooks/keyhook.c
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	movement_keyhook(t_game *g);

//src/init/init_ray.c
void	init_raycaster(t_game *g);

//src/textures.c
int		*create_color_array(t_game *g, mlx_texture_t *tex);
void	draw_half_tex(t_game *g);
#endif