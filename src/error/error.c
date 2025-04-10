/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:34:13 by fforster          #+#    #+#             */
/*   Updated: 2025/04/10 15:42:30 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// for fatal errors, cleans everything and prints error message
void	ft_error(char *msg, int errcode, t_game	*game)
{
	if (msg)
		printf("Error\n%s\nErrorcode: %d\n", msg, errcode);
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
		mlx_delete_texture(t->no_tex);
		if (t->wallcolors)
			ft_free(t->wallcolors);
	}
	if (t->so_tex)
	{
		mlx_delete_texture(t->so_tex);
		if (t->wallcolors)
			ft_free(t->wallcolors);
	}
	if (t->we_tex)
	{
		mlx_delete_texture(t->we_tex);
		if (t->wallcolors)
			ft_free(t->wallcolors);
	}
	if (t->ea_tex)
	{
		mlx_delete_texture(t->ea_tex);
		if (t->wallcolors)
			ft_free(t->wallcolors);
	}
}

void	ft_free_dp(char **dp)
{
	size_t	i;

	i = 0;
	if (!dp)
		return ;
	while (dp[i])
	{
		ft_free(dp[i]);
		dp[i] = NULL;
		i++;
	}
	ft_free(dp);
	dp = NULL;
}

void	parse_error(t_map *map, t_textures *tex, char *msg, char **raw_scene)
{
	if (raw_scene)
		ft_free_dp(raw_scene);
	if (map)
	{
		if (map->tiles)
			ft_free_dp(map->tiles);
		if (map->copy)
			ft_free_dp(map->copy);
	}
	if (tex)
		delete_textures(tex);
	if (msg)
		printf("Error\n%s\n", msg);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(1);
}
