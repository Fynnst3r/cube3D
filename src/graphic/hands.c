/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:55:02 by fforster          #+#    #+#             */
/*   Updated: 2025/04/24 15:22:03 by fforster         ###   ########.fr       */
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

static void	build_animation(t_game *g, double start, bool *end)
{
	if (start + 0.1 < mlx_get_time())
	{
		g->hands[4]->enabled = true;
		g->hands[5]->enabled = false;
	}
	if (start + 0.2 < mlx_get_time())
	{
		g->hands[4]->enabled = true;
		g->hands[5]->enabled = true;
	}
	if (start + 0.25 < mlx_get_time())
	{
		g->hands[4]->enabled = false;
		g->hands[5]->enabled = false;
		g->hands[6]->enabled = true;
		change_map_element(g, '0', 'D', g->map.tiles);
	}
	if (start + 0.5 < mlx_get_time())
	{
		g->hands[6]->enabled = false;
		*end = true;
	}
}

void	build_wall(t_game *g)
{
	static bool		animation_end = true;
	static double	start_time = 0.0;

	if (!g->player.build)
	{
		g->hands[4]->enabled = false;
		g->hands[5]->enabled = false;
		g->hands[6]->enabled = false;
		animation_end = true;
		return ;
	}
	if (animation_end)
		start_time = mlx_get_time();
	animation_end = false;
	build_animation(g, start_time, &animation_end);
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
	if (start_time + 0.35 < mlx_get_time())
	{
		hit_wall(g);
		animation_end = true;
	}
}
