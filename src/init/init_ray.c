/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:39:25 by fforster          #+#    #+#             */
/*   Updated: 2025/04/24 15:15:22 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
	if (d == 'N')
	{
		r->plane.y = 0;
		r->plane.x = FOV;
	}
	if (d == 'S')
	{
		r->plane.y = 0;
		r->plane.x = -FOV;
	}
	if (d == 'E')
	{
		r->plane.x = 0;
		r->plane.y = FOV;
	}
	if (d == 'W')
	{
		r->plane.x = 0;
		r->plane.y = -FOV;
	}
}

void	init_raycaster(t_game *g)
{
	decide_dir(&g->player);
	set_plane(&g->ray, g->player.looking);
}
