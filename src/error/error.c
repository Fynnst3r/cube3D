/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:34:13 by fforster          #+#    #+#             */
/*   Updated: 2025/02/17 13:37:16 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// for fatal errors, cleans everything and prints error message
void	ft_error(char *msg, int errcode, t_game	*game)
{
	if (msg)
		printf("ERROR %d: %s\n", errcode, msg);
	else if (mlx_errno != 0)
		printf("MLX ERROR: %s\n", mlx_strerror(mlx_errno));
	// delete_textures(game);
	if (game)
	{
		if (game->mlx)
			mlx_terminate(game->mlx);
	}
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(errcode);
}

// void	delete_textures(t_game *a)
// {
// 	if (a->textures.wall)
// 		mlx_delete_texture(a->textures.wall);
// }
