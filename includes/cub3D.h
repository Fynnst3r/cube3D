/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:10:10 by fforster          #+#    #+#             */
/*   Updated: 2025/02/17 15:51:16 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include "colors.h"
# include "garbage_collector.h"

typedef struct master_struct
{
	mlx_t		*mlx;

	mlx_image_t	*bg;
	mlx_image_t	*img;
}		t_game;

//src/hooks/keyhook.c
void	my_keyhook(mlx_key_data_t keydata, void *param);

//src/error.c
void	ft_error(char *msg, int errcode, t_game	*game);
// void	delete_textures(t_game *a);

#endif