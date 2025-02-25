/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:57 by fforster          #+#    #+#             */
/*   Updated: 2025/02/25 13:24:19 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// void	move_player(t_game *g, float y, float x)
// {
// 	g->img->instances->y += y;
// 	g->img->instances->x += x;
// }

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game					*game;
	// static mlx_key_data_t	lastkey;

	game = (t_game *)param;
	// printf("keyhook called\n");
	// printf("curr key %i\n", keydata.key);
	// printf("last key %i\n", lastkey.key);
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		ft_error("Game closed with esc.\n", 0, game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->img->instances->y -= MV_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->img->instances->y += MV_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->img->instances->x -= MV_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->img->instances->x += MV_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.dir.x--;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.dir.x++;
}
