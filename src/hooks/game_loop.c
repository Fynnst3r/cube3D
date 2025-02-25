/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:43:31 by fforster          #+#    #+#             */
/*   Updated: 2025/02/25 16:29:41 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	find_player(t_game *g)
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
				g->player.pos.x = x;
				g->player.pos.y = y;
			printf(ANSI_GREEN"player.pos.x = %f\nplayer.pos.y = %f\n"ANSI_RESET, g->player.pos.x, g->player.pos.y);
				found++;
				g->player.looking = g->map.tiles[y][x];
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (found);
}

void	init_raycaster(t_game *g)
{
	if (find_player(g) != 1)
		ft_error("Too many or no players!", 4, g);
	g->player.pos.x = 4;
	g->player.pos.y = 4;
	//look dir (N/E/S/W) N =(x = 0, y = -1)
	//					 E =(x = 1, y = 0)
	//					 W =(x = -1, y = 0)
	//					 S =(x = 0, y = 1)
	g->player.dir.x = 0;
	g->player.dir.y = 1;
	g->ray.plane.x = 0;
	g->ray.plane.y = 0.66;
}

void	raycaster_loop(void *param)
{
	t_game	*g;
	int		i;

	g = (t_game *)param;
	i = 0;
	//printf("i = %i xd\n", i);
	while (i < S_WIDTH)
	{
		// init_raycaster(g);
		g->ray.tile_x = (int)g->player.pos.x; //update when new tile has been entered
		g->ray.tile_y = (int)g->player.pos.y;
		g->ray.camera.x = 2 * i / (double)S_WIDTH - 1; //x-coordinate in camera space
		g->ray.ray_dir.x = g->player.dir.x + g->ray.plane.x * g->ray.camera.x;
		g->ray.ray_dir.y = g->player.dir.y + g->ray.plane.y * g->ray.camera.x;
		g->ray.delta_dist.x = fabs(1.0 / g->ray.ray_dir.x);
		if (g->ray.ray_dir.x == 0)
			g->ray.delta_dist.x = INFINITY;
		g->ray.delta_dist.y = fabs(1.0 / g->ray.ray_dir.y);
		if (g->ray.ray_dir.y == 0)
			g->ray.delta_dist.y = INFINITY;
	printf("deltax = %f xd\n", g->ray.delta_dist.x);
	printf("delta y = %f xd\n", g->ray.delta_dist.y);
	printf("i = %i xd\n", i);
		step_which_side(g);
printf(ANSI_UNDERLINE"main loop : %d\n"ANSI_RESET,  __LINE__);
		shoot_ray(g);
printf(ANSI_UNDERLINE"main loop : %d\n"ANSI_RESET,  __LINE__);
		draw_vertical_line(g, i);
printf(ANSI_UNDERLINE"main loop : %d\n"ANSI_RESET,  __LINE__);
		i++;
	}
}

//calc next tile to go/step in to and the first side_dist (closest x/y wall)
//if ray.dir.x/y is 0 it wont be used
void	step_which_side(t_game *g)
{
	// static int	i = 0;
		//printf("stepi = %i xd\n", i);
		// i++;
	// for x
	//printf("initial sidedistx %f\ninitial sidedist y %f\n", g->ray.side_dist.x, g->ray.side_dist.y);
	if (g->ray.ray_dir.x < 0)
	{
		//printf(ANSI_YELLOW"ray dir x %f ???????????\n"ANSI_RESET, g->ray.ray_dir.x);
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
	//printf("sidedistx %f\nsidedist y %f\n", g->ray.side_dist.x, g->ray.side_dist.y);
}

//DDA algo
void	shoot_ray(t_game *g)
{
	// static int	i = 0;
	// // 	//printf("shoti = %i xd\n", i);
	// 	i++;
	bool	x_wall;
	bool	y_wall;
	bool	hit_wall;

	hit_wall = false;
	// if (g->ray.go_x == 1)
	// 	ray_len = g->ray.side_dist.x;
	// if (g->ray.go_y == 1)
	// 	ray_len = g->ray.side_dist.y;
	while (!hit_wall)
	{
printf(ANSI_UNDERLINE"shoot loop : %d\n"ANSI_RESET,  __LINE__);
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
printf("y %i, x %i, shoot loop: %d\n", g->ray.tile_y, g->ray.tile_x, __LINE__);
		// if (g->map.tiles[g->ray.tile_y][g->ray.tile_x] > 0)
		if (g->map.tiles[g->ray.tile_y][g->ray.tile_x]
			&& (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '1'
				|| g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '2'))
		{
		printf("!!!HIT WALL!!! on y %i, x %i,\n", g->ray.tile_y, g->ray.tile_x);
			hit_wall = true;
		}
printf(ANSI_UNDERLINE"shoot loop : %d\n"ANSI_RESET,  __LINE__);
	}
	if (x_wall)
	{
		g->ray.perp_wall_dist = (g->ray.side_dist.x - g->ray.delta_dist.x);
		g->ray.hit_x_wall = true;
	}
	else
		g->ray.perp_wall_dist = (g->ray.side_dist.y - g->ray.delta_dist.y);
}

void	draw_vertical_line(t_game *g, int i)
{
	int	y;
	int	wall_height = (int)(S_HEIGHT / g->ray.perp_wall_dist);
	//printf("perpwalldist %f\n",g->ray.perp_wall_dist);
printf(ANSI_RED"wall height =				%i\n"ANSI_RESET, wall_height);
	int	draw_start = -wall_height / 2 + S_HEIGHT / 2;
	//printf("start %i\n", draw_start);
	int draw_end = wall_height + draw_start;
	//printf("end %i\n", draw_end);

	int	ceiling_color = get_rgba(20, 20, 255, 255);
		int	wall_color = get_rgba(130, 90, 0, 255);
		int	wall_color2 = get_rgba(250, 20, 20, 255);
	if (g->ray.hit_x_wall)
	{
		wall_color = get_rgba(50, 90, 0, 255);
		wall_color2 = get_rgba(135, 20, 20, 255);
	}
	int	floor_color = get_rgba(0, 130, 70, 255);

	y = 0;
	while (y < draw_start)
	{
	//printf("ydraw %i, line: %d\n", y, __LINE__);
		mlx_put_pixel(g->bg, i, y, ceiling_color);
		y++;
	}
	while (y < draw_end)
	{
	//printf("ydraw %i, line: %d\n", y, __LINE__);
		if (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '1')
			mlx_put_pixel(g->bg, i, y, wall_color);
		else if (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '2')
			mlx_put_pixel(g->bg, i, y, wall_color2);
	//printf("end %i\n", draw_end);
		y++;
	}
	while (y < S_HEIGHT)
	{
		mlx_put_pixel(g->bg, i, y, floor_color);
		y++;
	//printf("ydraw %i, line: %d\n", y, __LINE__);
	}
	//printf("AAAA\n");
}
