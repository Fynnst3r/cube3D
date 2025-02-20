/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:10:10 by fforster          #+#    #+#             */
/*   Updated: 2025/02/17 21:24:50 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef MV_SPEED
#  define MV_SPEED 10
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

}		t_game;

//src/hooks/keyhook.c
void	my_keyhook(mlx_key_data_t keydata, void *param);

//src/error.c
void	ft_error(char *msg, int errcode, t_game	*game);
// void	delete_textures(t_game *a);

#endif