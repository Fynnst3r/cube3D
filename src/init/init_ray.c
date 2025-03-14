/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:39:25 by fforster          #+#    #+#             */
/*   Updated: 2025/03/14 15:48:57 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	find_player(t_game *g)
{
	size_t	x;
	size_t	y;
	int		found;

	x = 0;
	y = 0;
	found = 0;
	while (g->map.tiles[y])
	{
		while (g->map.tiles[y][x])
		{
			if (g->map.tiles[y][x] == 'N' || g->map.tiles[y][x] == 'E'
				|| g->map.tiles[y][x] == 'S' || g->map.tiles[y][x] == 'W')
			{
				g->player.pos.x = x + 0.5;
				g->player.pos.y = y + 0.5;
			printf(ANSI_GREEN"player.pos.x = %f\nplayer.pos.y = %f\n"ANSI_RESET, g->player.pos.x, g->player.pos.y);
				found++;
				g->player.looking = g->map.tiles[y][x];
				g->map.tiles[y][x] = '0';
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (found);
}

//look dirs (N/E/S/W)
//						N =(x = 0, Y = -1)
//		W =(x = -1, Y = 0)				E =(x = 1, Y = 0)
//						S =(x = 0, Y = 1)
static void	decide_dir(t_player *p)
{
	if (p->looking == 'N')
	{
		p->dir.x = 0;
		p->dir.y = -1;
	}
	if (p->looking == 'E')
	{
		p->dir.x = 1;
		p->dir.y = 0;
	}
	if (p->looking == 'S')
	{
		p->dir.x = 0;
		p->dir.y = 1;
	}
	if (p->looking == 'W')
	{
		p->dir.x = -1;
		p->dir.y = 0;
	}
}

static void	set_plane(t_ray *r, char d)
{
	double	fov;

	fov = 0.77;
	if (d == 'N')
	{
		r->plane.y = 0;
		r->plane.x = fov;
	}
	if (d == 'S')
	{
		r->plane.y = 0;
		r->plane.x = -fov;
	}
	if (d == 'E')
	{
		r->plane.x = 0;
		r->plane.y = fov;
	}
	if (d == 'W')
	{
		r->plane.x = 0;
		r->plane.y = -fov;
	}
}

void	init_raycaster(t_game *g)
{
	if (find_player(g) != 1)
		ft_error("Too many or no players!", 4, g);
	decide_dir(&g->player);
	set_plane(&g->ray, g->player.looking);
}
