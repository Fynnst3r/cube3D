/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:34:13 by fforster          #+#    #+#             */
/*   Updated: 2025/04/06 21:32:39 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// for fatal errors, cleans everything and prints error message
void	ft_error(char *msg, int errcode, t_game	*game)
{
	if (msg)
		printf("%s\nErrorcode: %d\n", msg, errcode);
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

void	delete_textures(t_game *g)
{
	// if (g->textures.walltex)
	// {
	// 	mlx_delete_texture(g->textures.walltex);
	// 	if (g->textures.wallcolors)
	// 		ft_free(g->textures.wallcolors);
	// }
	if (g->textures[0].walltex)
	{
		mlx_delete_texture(g->textures[0].walltex);
		if (g->textures[0].wallcolors)
			ft_free(g->textures[0].wallcolors);
	}
	if (g->textures[1].walltex)
	{
		mlx_delete_texture(g->textures[1].walltex);
		if (g->textures[1].wallcolors)
			ft_free(g->textures[1].wallcolors);
	}
}
