/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:34:13 by fforster          #+#    #+#             */
/*   Updated: 2025/04/01 16:55:37 by fforster         ###   ########.fr       */
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
	// delete_textures(game->textures);
	if (game)
	{
		if (game->mlx)
			mlx_terminate(game->mlx);
	}
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(errcode);
}

void	delete_textures(t_textures *t)
{
	if (t->walltex)
	{
		mlx_delete_texture(t->walltex);
		if (t->wallcolors)
			ft_free(t->wallcolors);
	}
	if (t->no_tex)
	{
	}
	if (t->so_tex)
	{
	}
	if (t->we_tex)
	{
	}
	if (t->ea_tex)
	{
	}
}

void	parse_error(t_map *map, t_textures *tex, char *msg, int errcode)
{
	if (map)
		if (map->tiles)
			free(map->tiles);
	if (tex)
		delete_textures(tex);
	printf("Error\n%s\n", msg);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(errcode);
}
