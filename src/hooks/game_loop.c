/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:43:31 by fforster          #+#    #+#             */
/*   Updated: 2025/04/06 20:49:50 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	raycaster_loop(void *param)
{
	t_game	*g;
	int		x;

	g = (t_game *)param;
	x = 0;
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
	// printf("line %d\n", __LINE__);
		step_which_side(g);
// printf(ANSI_UNDERLINE"main loop : %d\n"ANSI_RESET,  __LINE__);
		shoot_ray(g);
// printf(ANSI_UNDERLINE"main loop shot ray: %d\n"ANSI_RESET,  __LINE__);
		ray_len_and_hitpoint(g->player, &g->ray);
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

//DDA algo
void	shoot_ray(t_game *g)
{
	bool	x_wall;
	bool	hit_wall;

	hit_wall = false;
	while (!hit_wall)
	{
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
		if (g->map.tiles[g->ray.tile_y][g->ray.tile_x]
			&& (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '1'
				|| g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '2'))
		{
		// printf("!!!HIT WALL!!! on y %zu, x %zu,\n", g->ray.tile_y, g->ray.tile_x);
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

// calc tx to the position where the ray would hit the texture
// calc steps which pixels to draw going downwards, wallheight is never the same
// figure out what to do if wallheight is higher than screen height when walking into wall
void	draw_vertical_line(t_game *g, int x)
{
	int	y;
	// double	tx = 0;
	// int		px = 0;
	unsigned int x_tx = 0;
	int	wall_height = (int)(S_HEIGHT / g->ray.perp_wall_dist);
	int	draw_start = -wall_height / 2 + S_HEIGHT / 2;
	int draw_end = wall_height + draw_start;
	if (draw_end > S_HEIGHT)
		draw_end = S_HEIGHT - 1;
	int	ceiling_color = get_rgba(20, 20, 255, 255);
	int	wall_color = get_rgba(130, 90, 0, 255);
	// int	wall_color = get_rgba(g->wall->pixels[y], g->wall->pixels[y + 1], g->wall->pixels[y + 2], g->wall->pixels[y + 3]);
	int	wall_color2 = get_rgba(250, 20, 20, 255);
	if (g->ray.hit_x_wall)
	{
		wall_color /= 2;
		wall_color2 /= 2;
	}
	int	floor_color = get_rgba(0, 130, 70, 255);

	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(g->bg, x, y, ceiling_color);
		y++;
	}
	double y_proportion = (((double) g->textures[0].walltex->height / (double) wall_height));
	int	y_tx = y * y_proportion;
	y_tx *= g->textures->walltex->width;
	// max array = (width * heigth * 4) - 1;
	// printf("\n%s %d height * width  %d  -1)* 4 %d y_tx %d \n", __FILE__, __LINE__, 
	// 	g->textures->walltex->width * g->textures->walltex->height, 
	// 	(g->textures->walltex->width * g->textures->walltex->height -1) *4, y_tx);
	while (y < draw_end)
	// while ((y < draw_end) && ((y_tx + 3) < (g->textures->walltex->width * g->textures->walltex->height * 4)))
	{
		// printf("%s %d y %d draw_start %d y_tx %d r %d g %d b %d a %d\n", __FILE__,
		//        __LINE__, y, draw_start, y_tx, g->textures[0].walltex->pixels[y_tx], g->textures[0].walltex->pixels[y_tx + 1], 
		// 	g->textures[0].walltex->pixels[y_tx + 2], g->textures[0].walltex->pixels[y_tx + 3]);
		if ((y_tx + 3) <= (g->textures->walltex->width * g->textures->walltex->height * 4))
		{
			// printf("%s %d y %d  y_tx %d \n", __FILE__, __LINE__, y, y_tx);
			wall_color = get_rgba(g->textures[0].walltex->pixels[y_tx], g->textures[0].walltex->pixels[y_tx + 1], 
							g->textures[0].walltex->pixels[y_tx + 2], g->textures[0].walltex->pixels[y_tx + 3]);
			if (g->ray.hit_x_wall)
			{
				// wall_color /= 2;
				// wall_color2 /= 2;
			}
			mlx_put_pixel(g->bg, x, y, wall_color);
		}
			y++;
			// // this makes it in proportion
			y_tx = round((y - draw_start) * y_proportion);
			// // printf("%s %d y %d  y_tx %d \n", __FILE__, __LINE__, y, y_tx);
			if (y_tx >= g->textures->walltex->height)
				y_tx = g->textures->walltex->height - 1;

			y_tx *= g->textures->walltex->width;
			// printf("%s %d y %d  y_tx %d \n", __FILE__, __LINE__, y, y_tx);
			// //
			// //I need to times 4 to get to the right px. I just see the right px 
			// // colour values not distorted as 100, which is the width of my current texture is %4
			// y_tx *= 4;
			// //get x from proportion
			// // if hit x than x_intersect is callc from right to left, therefore it is
			// // (1 - x_intersect)
			// if (g->ray.hit_x_wall)
			// 	x_tx = round((1 - g->ray.x_intersect) * g->textures[0].walltex->width);
			// else
			x_tx = round(g->ray.x_intersect * g->textures[0].walltex->width);	
			if ((g->ray.hit_x_wall  && g->ray.ray_dir.x < 0)
				|| (!g->ray.hit_x_wall && g->ray.ray_dir.y > 0))
				x_tx = round((1 - g->ray.x_intersect) * g->textures[0].walltex->width);
			else
				x_tx = round(g->ray.x_intersect * g->textures[0].walltex->width);	
			if ( x_tx >= g->textures[0].walltex->width)
				x_tx = g->textures[0].walltex->width - 1;
			// printf("%s %d x_intersect %f  tx width %d   x_tx %d\n", __FILE__, __LINE__,
			// 			g->ray.x_intersect, g->textures->walltex->width, x_tx);
			// // add x but each 4th is the start
			// y_tx += x_tx * 4;
			y_tx += x_tx;
			y_tx *= 4;
			// printf("%s %d y %d draw_start %d y_tx %d r %d g %d b %d a %d\n", __FILE__,
			// 		__LINE__, y, draw_start, y_tx, g->textures[0].walltex->pixels[y_tx],
			// 		g->textures[0].walltex->pixels[y_tx + 1], 
			// 		g->textures[0].walltex->pixels[y_tx + 2], 
			// 		g->textures[0].walltex->pixels[y_tx + 3]);
	}
	// printf("%s %d y_tx %d x_tx %d\n", __FILE__, __LINE__, y_tx, x_tx);
	// printf("%s %d x_intersect %f  tx width %d   x_tx %d\n", __FILE__, __LINE__,
	// 		g->ray.x_intersect, g->textures->walltex->width, x_tx);
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
