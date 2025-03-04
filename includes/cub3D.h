/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:10:10 by fforster          #+#    #+#             */
/*   Updated: 2025/02/26 14:14:26 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef MV_SPEED
#  define MV_SPEED 10
# endif

# ifndef MV_SPEED_MINI
#  define MV_SPEED_MINI 1
# endif

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "garbage_collector.h"
# include "colors.h"
# include "../MLX42/include/MLX42/MLX42.h"


typedef struct coordinates
{
	float	y;
	float	x;

}		t_cords;

typedef struct	coordinates_int32
{
	int32_t	y;
	int32_t	x;

}		t_cords_int32;

typedef struct	height_width
{
	u_int32_t	height;
	u_int32_t	width;
}				t_height_width;

typedef struct map
{
	char	**tiles;

	size_t	max_y;
	size_t	max_x;

}		t_map;

typedef struct master_struct
{
	mlx_t			*mlx;

	mlx_image_t		*bg;
	mlx_image_t		*img;
	mlx_image_t		*wall;
	mlx_texture_t	*walltex;
	t_map			map;
	mlx_image_t		*minimap;
	mlx_image_t		*miniplayer;
	mlx_image_t		*line;
	int	dir_x;
	int	dir_y;
}		t_game;

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