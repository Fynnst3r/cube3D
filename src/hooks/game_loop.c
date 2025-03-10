/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:43:31 by fforster          #+#    #+#             */
/*   Updated: 2025/03/10 20:47:01 by fforster         ###   ########.fr       */
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
void	decide_dir(t_player *p)
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

void	set_plane(t_ray *r, char d)
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

void	raycaster_loop(void *param)
{
	t_game	*g;
	int		x;

	g = (t_game *)param;
	x = 0;
	//printf("i = %i xd\n", i);
	while (x < S_WIDTH)
	{
		g->ray.tile_x = (int)g->player.pos.x; //update when new tile has been entered
		g->ray.tile_y = (int)g->player.pos.y;
		g->ray.camera_x = 2 * x / (double)S_WIDTH - 1; //x-coordinate in camera space
		g->ray.ray_dir.x = g->player.dir.x + g->ray.plane.x * g->ray.camera_x;
		g->ray.ray_dir.y = g->player.dir.y + g->ray.plane.y * g->ray.camera_x;
		if (g->ray.ray_dir.x == 0)
			g->ray.delta_dist.x = INFINITY;
		else
			g->ray.delta_dist.x = fabs(1.0 / g->ray.ray_dir.x);
		if (g->ray.ray_dir.y == 0)
			g->ray.delta_dist.y = INFINITY;
		else
			g->ray.delta_dist.y = fabs(1.0 / g->ray.ray_dir.y);
	// printf("deltax = %f xd\n", g->ray.delta_dist.x);
	// printf("delta y = %f xd\n", g->ray.delta_dist.y);
	// printf("i = %i xd\n", i);
	// printf("line %d\n", __LINE__);
		step_which_side(g);
	// printf("line %d\n", __LINE__);
// printf(ANSI_UNDERLINE"main loop : %d\n"ANSI_RESET,  __LINE__);
// printf("line %d\n", __LINE__);
		shoot_ray(g);
// printf(ANSI_UNDERLINE"main loop shot ray: %d\n"ANSI_RESET,  __LINE__);
		draw_vertical_line(g, x);
		x++;
	}
	movement_keyhook(g);
}

//calc next tile to go/step in to and the first side_dist (closest x/y wall)
//if ray.dir.x/y is 0 it wont be used
void	step_which_side(t_game *g)
{
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
	bool	x_wall;
	bool	hit_wall;

	hit_wall = false;
	while (!hit_wall)
	{
		// printf("line %d\n", __LINE__);
		// printf(ANSI_UNDERLINE"shoot loop : %d\n"ANSI_RESET,  __LINE__);
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
// printf("y %zu, x %zu, shoot loop: %d\n", g->ray.tile_y, g->ray.tile_x, __LINE__);
		// if (g->map.tiles[g->ray.tile_y][g->ray.tile_x] > 0)
		if (g->map.max_x < g->ray.tile_x || g->ray.tile_y > g->map.max_y)
			break ;
		if (g->map.tiles[g->ray.tile_y][g->ray.tile_x]
			&& (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '1'
				|| g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '2'))
		{
			// printf("line %d\n", __LINE__);
		// printf("!!!HIT WALL!!! on y %zu, x %zu,\n", g->ray.tile_y, g->ray.tile_x);
			hit_wall = true;
		}
// printf(ANSI_UNDERLINE"shoot loop : %d\n"ANSI_RESET,  __LINE__);
	}
	if (x_wall)
		g->ray.perp_wall_dist = (g->ray.side_dist.x - g->ray.delta_dist.x);
	else
		g->ray.perp_wall_dist = (g->ray.side_dist.y - g->ray.delta_dist.y);
	g->ray.hit_x_wall = x_wall;
}

void	draw_vertical_line(t_game *g, int x)
{
	int	y;
	int	wall_height = (int)(S_HEIGHT / g->ray.perp_wall_dist);
	//printf("perpwalldist %f\n",g->ray.perp_wall_dist);
	// printf(ANSI_RED"wall height =				%i\n"ANSI_RESET, wall_height);
	int	draw_start = -wall_height / 2 + S_HEIGHT / 2;
	int draw_end = wall_height + draw_start;
	if (draw_end > S_HEIGHT)
		draw_end = S_HEIGHT - 1;
	int	ceiling_color = get_rgba(20, 20, 255, 255);
	int	wall_color = get_rgba(130, 90, 0, 255);
	int	wall_color2 = get_rgba(250, 20, 20, 255);
	if (g->ray.hit_x_wall)
	{
		wall_color /= 2;
		wall_color2 /= 2;
	}
	int	floor_color = get_rgba(0, 130, 70, 255);
	y = 0;
	// printf(ANSI_RED"start %i\n", draw_start);
	// printf("end %i\n"ANSI_RESET, draw_end);
	// if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_CONTROL))
	// {
	// 	draw_start /= 4;
	// 	draw_end = draw_start + wall_height;
	// }
	while (y < draw_start)
	{
		mlx_put_pixel(g->bg, x, y, ceiling_color);
		y++;
	}
	while (y < draw_end)
	{
		// if (g->map.max_x > g->ray.tile_x && g->ray.tile_y < g->map.max_y)
		// {
			if (g->map.tiles[g->ray.tile_y][g->ray.tile_x]
				&& g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '1')
				mlx_put_pixel(g->bg, x, y, wall_color);
			else if (g->map.tiles[g->ray.tile_y][g->ray.tile_x]
					&& g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '2')
				mlx_put_pixel(g->bg, x, y, wall_color2);
		// }
		y++;
	}
	while (y < S_HEIGHT)
	{
		mlx_put_pixel(g->bg, x, y, floor_color);
		y++;
	}
}

//calculates lenght between two points
// double veclen(double x1, double y1, double x2, double y2)
// {
// 	return (sqrt((pow((x2 - x1), 2) + pow((y2 - y1), 2))));
// }

//prints various info of the state of the ray for debug
void	print_ray_status(t_game *g)
{
	printf(ANSI_GREEN"PLAYER y %f - PLAYER x %f\n"ANSI_RESET, g->player.pos.y, g->player.pos.x);
	printf("PLAYERdir x %f - PLAYERdir y %f\n", g->player.dir.x, g->player.dir.y);
	printf("plane x %f - plane y %f\n", g->ray.plane.x, g->ray.plane.y);
	printf("camera x %f\n", g->ray.camera_x);
	printf(ANSI_BLUE"ray tile x %zu - y %zu\n"ANSI_RESET, g->ray.tile_x, g->ray.tile_y);
	printf("ray_dir x %f - ray_dir y %f\n", g->ray.ray_dir.x, g->ray.ray_dir.y);
	printf(ANSI_YELLOW"side_dist x %f - side_dist y %f\n"ANSI_RESET, g->ray.side_dist.x, g->ray.side_dist.y);
	printf(ANSI_MAGENTA"delta_dist x %f - delta_dist y %f\n"ANSI_RESET, g->ray.delta_dist.x, g->ray.delta_dist.y);
	printf("perpendicular_wall_dist %f\n", g->ray.perp_wall_dist);
	printf("go x %i, go y %i\n\n", g->ray.go_x, g->ray.go_y);
}
