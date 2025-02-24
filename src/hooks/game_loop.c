/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:43:31 by fforster          #+#    #+#             */
/*   Updated: 2025/02/24 18:11:46 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_raycaster(t_game *g)
{
	g->player.pos.x = 4; //set to spawn later
	g->player.pos.y = 4;
	g->ray.tile_x = (int)g->player.pos.x; // update when new tile has been entered
	g->ray.tile_y = (int)g->player.pos.y;
	g->player.dir.x = 1; //initial look dir (N/E/S/W) x = 1 = E
	g->player.dir.y = 0;
	g->ray.plane.x = 0;
	g->ray.plane.y = 0.66;
}

void	raycaster_loop(t_game *g)
{
	int	i;

	i = 4;
		printf("i = %i xd\n", i);
	while (i < S_WIDTH)
	{
		g->ray.camera.x = 2 * i / (double)S_WIDTH - 1; //x-coordinate in camera space
		g->ray.ray_dir.x = g->player.dir.x + g->ray.plane.x * g->ray.camera.x;
		g->ray.ray_dir.y = g->player.dir.y + g->ray.plane.y * g->ray.camera.x;
		g->ray.delta_dist.x = fabs(1.0 / g->ray.ray_dir.x);
		if (g->ray.ray_dir.x == 0)
			g->ray.delta_dist.x = INFINITY;
		g->ray.delta_dist.y = fabs(1.0 / g->ray.ray_dir.y);
		if (g->ray.ray_dir.y == 0)
			g->ray.delta_dist.y = INFINITY;
		printf("i = %i xd\n", i);
		step_which_side(g);
		shoot_ray(g);
		i++;
	}
}

//calc next tile to go/step in to and the first side_dist (closest x/y wall)
//if ray.dir.x/y is 0 it wont be used
void	step_which_side(t_game *g)
{
	// for x
	static int	i = 0;
		printf("stepi = %i xd\n", i);
		i++;
	if (g->ray.ray_dir.x < 0)
	{
		g->ray.go_x = -1;
		g->ray.side_dist.x = (g->player.pos.x - g->ray.tile_x)
			* g->ray.delta_dist.x;
	}
	else
	{
		g->ray.go_x = 1;
		g->ray.side_dist.x = (g->ray.tile_x + 1.0 - g->player.pos.x)
			* g->ray.delta_dist.x;
	}
	// for y
	if (g->ray.ray_dir.y < 0)
	{
		g->ray.go_y = -1;
		g->ray.side_dist.y = (g->player.pos.y - g->ray.tile_y)
			* g->ray.delta_dist.y;
	}
	else
	{
		g->ray.go_y = 1;
		g->ray.side_dist.y = (g->ray.tile_y + 1.0 - g->player.pos.y)
			* g->ray.delta_dist.y;
	}
}

void	shoot_ray(t_game *g)
{
	static int	i = 0;
		printf("shoti = %i xd\n", i);
		i++;
	bool	x_wall;
	bool	y_wall;
	bool	hit_wall;
	int		wall_height;

	hit_wall = false;
	// if (g->ray.go_x == 1)
	// 	ray_len = g->ray.side_dist.x;
	// if (g->ray.go_y == 1)
	// 	ray_len = g->ray.side_dist.y;
	while (!hit_wall)
	{
		x_wall = false;
		y_wall = false;
		if (g->ray.side_dist.y > g->ray.side_dist.x)
		{
			g->ray.side_dist.x += g->ray.side_dist.x + g->ray.delta_dist.x;
			g->ray.tile_x += (int)g->ray.go_x;
			x_wall = true;
		}
		else
		{
			g->ray.side_dist.y += g->ray.side_dist.y + g->ray.delta_dist.y;
			g->ray.tile_y += (int)g->ray.go_y;
			y_wall = true;
		}
		if (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '1')
			hit_wall = true;
	}
	if (x_wall)
		g->ray.perp_wall_dist = (g->ray.side_dist.x - g->ray.side_dist.x);
	else
		g->ray.perp_wall_dist = (g->ray.side_dist.y - g->ray.side_dist.y);
	wall_height = (int)(S_HEIGHT / g->ray.perp_wall_dist);
}
