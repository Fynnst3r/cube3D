/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:55:02 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 18:19:06 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	change_map_element(t_game *g, char src, char dest, char **m)
{
	if (g->player.look_x_wall)
	{
		if (m[(size_t)g->player.pos.y][(size_t)g->player.pos.x + 1] == src
			&& g->player.dir.x > 0)
			m[(size_t)g->player.pos.y][(size_t)g->player.pos.x + 1] = dest;
		else if (m[(size_t)g->player.pos.y][(size_t)g->player.pos.x - 1] == src
				&& g->player.dir.x < 0)
			m[(size_t)g->player.pos.y][(size_t)g->player.pos.x - 1] = dest;
		else
			return (false);
	}
	else
	{
		if (m[(size_t)g->player.pos.y + 1][(size_t)g->player.pos.x] == src
			&& g->player.dir.y > 0)
			m[(size_t)g->player.pos.y + 1][(size_t)g->player.pos.x] = dest;
		else if (m[(size_t)g->player.pos.y - 1][(size_t)g->player.pos.x] == src
			&& g->player.dir.y < 0)
			m[(size_t)g->player.pos.y - 1][(size_t)g->player.pos.x] = dest;
		else
			return (false);
	}
	g->changed_map = true;
	return (true);
}

static void	hit_wall(t_game *g)
{
	g->hands[2]->enabled = false;
	g->hands[1]->enabled = true;
	if (!change_map_element(g, '1', '2', g->map.tiles))
		if (!change_map_element(g, 'D', 'd', g->map.tiles))
			change_map_element(g, 'd', '0', g->map.tiles);
	g->player.punch = false;
}

void	punch(t_game *g)
{
	static double	start_time = 0.0;
	static bool		animation_end = true;

	if (animation_end)
		start_time = mlx_get_time();
	animation_end = false;
	g->hands[1]->enabled = false;
	g->hands[2]->enabled = true;
	if (start_time + 0.1 < mlx_get_time())
	{
		g->hands[2]->enabled = false;
		g->hands[3]->enabled = true;
	}
	if (start_time + 0.33 < mlx_get_time())
	{
		g->hands[3]->enabled = false;
		g->hands[2]->enabled = true;
	}
	if (start_time + 0.38 < mlx_get_time())
	{
		hit_wall(g);
		animation_end = true;
	}
}

static void	move_hands(t_game *g, double direction_x, double direction_y)
{
	int	factor;

	factor = 2;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT))
		factor = 3;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SUPER))
		factor = 1;
	g->hands[0]->instances->x += direction_x * factor;
	g->hands[1]->instances->x += direction_x * factor;
	g->hands[0]->instances->y += direction_y * factor;
	g->hands[1]->instances->y += direction_y * factor;
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
		g->hands[0]->instances->x = S_WIDTH - x - g->hands[0]->width;
		g->hands[1]->instances->x = x;
		g->hands[0]->instances->y = S_HEIGHT - g->hands[0]->height + 15;
		g->hands[1]->instances->y = S_HEIGHT - g->hands[1]->height + 15;
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
