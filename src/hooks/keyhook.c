/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:57 by fforster          #+#    #+#             */
/*   Updated: 2025/02/17 14:51:59 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	move_player(t_game *g, float y, float x)
{
	g->img->instances->y += y;
	g->img->instances->x += x;
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game					*game;
	static mlx_key_data_t	lastkey;

	game = (t_game *)param;
	printf("keyhook called\n");
	printf("curr key %i\n", keydata.key);
	printf("last key %i\n", lastkey.key);
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		ft_error("Game closed with esc.\n", 0, game);
	}
	// if (lastkey.action != )
	// 	lastkey = keydata;
// }
	// // if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
	// // 	&& (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
	// // 	&& keydata.action != MLX_RELEASE)
	// // 	move_hero(game, -5, 5);
	// // if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
	// // 	&& (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
	// // 	&& keydata.action != MLX_RELEASE)
	// // 	move_hero(game, 5, 5);
	// // if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
	// // 	&& (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
	// // 	&& keydata.action != MLX_RELEASE)
	// // 	move_hero(game, 5, -5);
	// // if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
	// // 	&& (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
	// // 	&& keydata.action != MLX_RELEASE)
	// // 	move_hero(game, -5, -5);

	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		&& keydata.action != MLX_RELEASE)
		// && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, -5, 0);
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		&& keydata.action != MLX_RELEASE)
		// && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 5, 0);
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		&& keydata.action != MLX_RELEASE)
		// && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 0, -5);
	if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		&& keydata.action != MLX_RELEASE)
		// && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 0, 5);
}
