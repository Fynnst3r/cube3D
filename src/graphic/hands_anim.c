/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:19:22 by fforster          #+#    #+#             */
/*   Updated: 2025/04/24 15:20:08 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	move_hands(t_game *g, double direction_x, double direction_y)
{
	int	factor;

	factor = 2;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT)
		&& !mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SUPER))
		factor = 3;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SUPER)
		&& !mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT))
		factor = 1;
	g->hands[0]->instances->x += direction_x * factor;
	g->hands[1]->instances->x += direction_x * factor;
	g->hands[2]->instances->x += direction_x * factor;
	g->hands[3]->instances->x += direction_x * factor;
	g->hands[4]->instances->x += direction_x * factor;
	g->hands[5]->instances->x += direction_x * factor;
	g->hands[6]->instances->x += direction_x * factor;
	g->hands[0]->instances->y += direction_y * factor;
	g->hands[1]->instances->y += direction_y * factor;
	g->hands[2]->instances->y += direction_y * factor;
	g->hands[3]->instances->y += direction_y * factor;
	g->hands[4]->instances->y += direction_y * factor;
	g->hands[5]->instances->y += direction_y * factor;
	g->hands[6]->instances->y += direction_y * factor;
}

void	reset_hands(t_game *g)
{
	int	x;

	x = (S_WIDTH -(3 * ((g->hands[0]->width + g->hands[1]->width) / 2))) / 2;
	g->hands[0]->instances->x = S_WIDTH - x - g->hands[0]->width;
	g->hands[1]->instances->x = x;
	g->hands[2]->instances->x = x;
	g->hands[3]->instances->x = x;
	g->hands[4]->instances->x = S_WIDTH - x - g->hands[4]->width;
	g->hands[5]->instances->x = S_WIDTH - x - g->hands[5]->width;
	g->hands[6]->instances->x = S_WIDTH - x - g->hands[6]->width;
	g->hands[0]->instances->y = S_HEIGHT - g->hands[0]->height + 15;
	g->hands[1]->instances->y = S_HEIGHT - g->hands[1]->height + 15;
	g->hands[2]->instances->y = S_HEIGHT - g->hands[2]->height + 15;
	g->hands[3]->instances->y = S_HEIGHT - g->hands[3]->height + 15;
	g->hands[4]->instances->y = S_HEIGHT - g->hands[4]->height + 15;
	g->hands[5]->instances->y = S_HEIGHT - g->hands[5]->height + 15;
	g->hands[6]->instances->y = S_HEIGHT - g->hands[6]->height + 15;
}

void	sway_hands(t_game *g)
{
	static double	direction_x = 1;
	static double	direction_y = -1;
	int				max_y;
	int				min_y;
	int				x;

	x = (S_WIDTH -(3 * ((g->hands[0]->width + g->hands[1]->width) / 2))) / 2;
	if (!g->player.moving)
	{
		reset_hands(g);
		return ;
	}
	max_y = S_HEIGHT - g->hands[0]->height + 11 + 15;
	min_y = max_y - 22;
	if (g->hands[1]->instances->x > x + 22
		|| x - 22 > g->hands[1]->instances->x)
		direction_x *= -1;
	if (g->hands[0]->instances->y > max_y || min_y > g->hands[0]->instances->y)
		direction_y *= -1;
	move_hands(g, direction_x, direction_y);
}
