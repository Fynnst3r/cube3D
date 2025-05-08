/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:43:31 by fforster          #+#    #+#             */
/*   Updated: 2025/05/08 16:46:47 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	set_ray_delta_distance(t_game *game);

static void	set_ray_delta_distance(t_game *game)
{
	if (game->ray.ray_dir.x == 0)
		game->ray.delta_dist.x = INFINITY;
	else
		game->ray.delta_dist.x = fabs(1.0 / game->ray.ray_dir.x);
	if (game->ray.ray_dir.y == 0)
		game->ray.delta_dist.y = INFINITY;
	else
		game->ray.delta_dist.y = fabs(1.0 / game->ray.ray_dir.y);
}

void	raycaster_loop(void *param)
{
	t_game	*g;
	int		x;

	g = (t_game *)param;
	x = 0;
	while (x < S_WIDTH)
	{
		g->ray.tile_x = (int)g->player.pos.x;
		g->ray.tile_y = (int)g->player.pos.y;
		g->ray.camera_x = 2 * x / (double)S_WIDTH - 1;
		g->ray.ray_dir.x = g->player.dir.x + g->ray.plane.x * g->ray.camera_x;
		g->ray.ray_dir.y = g->player.dir.y + g->ray.plane.y * g->ray.camera_x;
		set_ray_delta_distance(g);
		step_which_side(g);
		shoot_ray(g);
		if (x == S_WIDTH / 2)
			g->player.look_x_wall = g->ray.hit_x_wall;
		ray_len_and_hitpoint(g->player, &g->ray);
		draw_vertical_line(g, x);
		x++;
	}
	movement_keyhook(g);
	hands_keyhook(g);
	minimap_keyhook(g);
}

//calc next tile to go/step in to and the first side_dist (closest x/y wall)
//if ray.dir.x/y is 0 it wont be used
// for x
// for y
void	step_which_side(t_game *g)
{
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

//DDA algo
void	shoot_ray(t_game *g)
{
	bool	x_wall;
	bool	hit_wall;

	hit_wall = false;
	while (!hit_wall)
	{
		if (g->ray.side_dist.y > g->ray.side_dist.x)
		{
			g->ray.side_dist.x += g->ray.delta_dist.x;
			g->ray.tile_x += (size_t)g->ray.go_x;
			x_wall = true;
		}
		else
		{
			g->ray.side_dist.y += g->ray.delta_dist.y;
			g->ray.tile_y += (size_t)g->ray.go_y;
			x_wall = false;
		}
		if (g->map.tiles[g->ray.tile_y][g->ray.tile_x]
			&& (g->map.tiles[g->ray.tile_y][g->ray.tile_x] != '0'))
		{
			hit_wall = true;
		}
	}
	g->ray.hit_x_wall = x_wall;
}

void	ray_len_and_hitpoint(const t_player p, t_ray *r)
{
	if (r->hit_x_wall)
	{
		r->perp_wall_dist = (r->side_dist.x - r->delta_dist.x);
		r->x_intersect = p.pos.y + r->perp_wall_dist * r->ray_dir.y;
	}
	else
	{
		r->perp_wall_dist = (r->side_dist.y - r->delta_dist.y);
		r->x_intersect = p.pos.x + r->perp_wall_dist * r->ray_dir.x;
	}
	r->x_intersect -= floor(r->x_intersect);
}
