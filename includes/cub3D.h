/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:10:10 by fforster          #+#    #+#             */
/*   Updated: 2025/03/13 15:11:11 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef MOVEMENT_SPEED
#  define MV_SPEED 10.0
# endif

# ifndef ROTATE_SP
#  define RT_SPEED 5.0
# endif

# ifndef S_WIDTH
#  define S_WIDTH 960
// #  define S_WIDTH 1600
# endif

# ifndef S_HEIGHT
#  define S_HEIGHT 540
// #  define S_HEIGHT 900
# endif

# ifndef MINI
#  define MINI_RESIZE_FACTOR 3
#  define MINI_UNITS_PER_TILE 10
// #  define MINI_PLAYER_WIDTH 10
// #  define MINI_PLAYER_HEIGHT 10
#  define MINI_PLAYER_WIDTH MINI_UNITS_PER_TILE
#  define MINI_PLAYER_HEIGHT MINI_UNITS_PER_TILE
#  define MINI_LINE_HEIGHT 3
#  define MINI_LINE_WIDTH 3
// #  define MV_SPEED_MINI 1
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

typedef struct	coordinates_int32
{
	int32_t	y;
	int32_t	x;
	
}		t_cords_int32;

//<<<<<<< fforster
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

//=======

typedef struct	height_width
{
	u_int32_t	height;
	u_int32_t	width;
}				t_height_width;

//>>>>>>> nsloniow_pullFynn

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
	int		tile_y;
	int		tile_x;

	//camera plane
	t_cords	plane;

	//x-coordinate in camera space
	t_cords	camera;

	//direction of a singular (current) rayf, our eyesight
	t_cords	ray_dir;

	// length of the ray from current pos to the closest x/y wall,
	// will increase when to the lenght of the shot ray using delta dist
	t_cords	side_dist;

	//length of ray from one x or y-side to next x or y-side
	t_cords	delta_dist;
	double	perp_wall_dist;
	bool	hit_x_wall;
	int		go_y;
	int		go_x;

}		t_ray;

typedef struct master_struct
{
	mlx_t			*mlx;

	mlx_image_t		*bg;
	mlx_image_t		*img;
	mlx_image_t		*wall;
	mlx_texture_t	*walltex;
	t_map			map;
//<<<<<<< fforster
	t_player		player;
	t_ray			ray;

	int				screen_width;
	int				screen_height;
	double			time;
	double			oldtime;

//=======
	mlx_image_t		*minimap;
	mlx_image_t		*miniplayer;
	mlx_image_t		*line;
	double			dir_x;
	double			dir_y;
//>>>>>>> nsloniow_pullFynn
}		t_game;

//src/main.c
int		get_rgba(int r, int g, int b, int a);

//src/hooks/game_loop.c
void	init_raycaster(t_game *g);
void	raycaster_loop(void *param);
void	step_which_side(t_game *g);
void	shoot_ray(t_game *g);
void	draw_vertical_line(t_game *g, int i);
void	print_ray_status(t_game *g);

//src/hooks/keyhook.c
void	my_keyhook(mlx_key_data_t keydata, void *param);

//src/error.c
void	ft_error(char *msg, int errcode, t_game	*game);
// void	delete_textures(t_game *a);

//src/graphic/image.c
void	draw_mini_map(t_game game);
void	draw_mini_player(t_game *game);
void	draw_line(t_game *game);
int		get_rgba(int r, int g, int b, int a);
void	pixset(mlx_image_t *img, int colour);
void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
			t_height_width height_width);
#endif