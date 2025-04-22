/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:43:31 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 14:56:21 by fforster         ###   ########.fr       */
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
		if (x == S_WIDTH / 2)
			g->player.look_x_wall = g->ray.hit_x_wall;
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
			&& (g->map.tiles[g->ray.tile_y][g->ray.tile_x] != '0'))
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
// void	draw_vertical_line(t_game *g, int x)
// {
// 	int				y;
// 	// unsigned int	x_tx = 0;
// 	int				wall_height = (int)(S_HEIGHT / g->ray.perp_wall_dist);
// 	int				draw_start = -wall_height / 2 + S_HEIGHT / 2;
// 	int				draw_end = wall_height + draw_start;
// 	int				ceiling_color = get_rgba(20, 20, 255, 255);
// 	int				wall_color = get_rgba(200, 0, 5, 255);
// 	int				wall_color2 = get_rgba(0, 200, 5, 255);
// 	int				floor_color = get_rgba(0, 130, 70, 255);

// 	if (draw_end > S_HEIGHT)
// 		draw_end = S_HEIGHT - 1;
// 	y = 0;
// 	while (y < draw_start)
// 	{
// 		mlx_put_pixel(g->bg, x, y, ceiling_color);
// 		y++;
// 	}
// 	// double y_proportion = (((double) g->textures[0].walltex->height / (double) wall_height));
// 	// int	y_tx = 0;
// 	while (y < draw_end)
// 	{
// // 		if ((y_tx + 3) <= (int)(g->textures->walltex->width * g->textures->walltex->height * 4))
// // 		{

// // mlx_texture_t	*tex;
// // if (g->ray.hit_x_wall)
// // 	tex = (g->ray.ray_dir.x > 0) ? g->textures[0].walltex : g->textures[1].walltex;
// // else
// // 	tex = (g->ray.ray_dir.y > 0) ? g->textures[2].walltex : g->textures[3].walltex;

// // 			// wall_color = get_rgba(g->textures[0].walltex->pixels[y_tx], g->textures[0].walltex->pixels[y_tx + 1], 
// // 			// 				g->textures[0].walltex->pixels[y_tx + 2], g->textures[0].walltex->pixels[y_tx + 3]);
// // 			wall_color = get_rgba(tex->pixels[y_tx], tex->pixels[y_tx + 1], 
// // 				tex->pixels[y_tx + 2], tex->pixels[y_tx + 3]);
// // 			mlx_put_pixel(g->bg, x, y, wall_color);
// // 		}
// // 			y++;
// // 			// this makes it in proportion
// // 			y_tx = round((y - draw_start) * y_proportion);
// // 			if (y_tx >= (int)g->textures->walltex->height)
// // 				y_tx = g->textures->walltex->height - 1;
// // 			y_tx *= g->textures->walltex->width;
// // 			x_tx = round(g->ray.x_intersect * g->textures[0].walltex->width);	
// // 			if ((g->ray.hit_x_wall  && g->ray.ray_dir.x < 0)
// // 				|| (!g->ray.hit_x_wall && g->ray.ray_dir.y > 0))
// // 				x_tx = round((1 - g->ray.x_intersect) * g->textures[0].walltex->width);
// // 			else
// // 				// x_tx = round(g->ray.x_intersect * g->textures[0].walltex->width);	
// // 				x_tx = round(g->ray.x_intersect * g->textures[0].walltex->width);	
// // 			if ( x_tx >= g->textures[0].walltex->width)
// // 				x_tx = g->textures[0].walltex->width - 1;
// // 			y_tx += x_tx;
// // 			y_tx *= 4;
// 					// printf("y %d\n", y);
// 		if (g->map.tiles[g->ray.tile_y][g->ray.tile_x]
// 			&& g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '1')
// 			mlx_put_pixel(g->bg, x, y, wall_color);
// 		else if (g->map.tiles[g->ray.tile_y][g->ray.tile_x]
// 				&& g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '2')
// 			mlx_put_pixel(g->bg, x, y, wall_color2);

// 		y++;
// 	}
// 	while (y < S_HEIGHT)
// 	{
// 		mlx_put_pixel(g->bg, x, y, floor_color);
// 		y++;
// 	}
// 	if (g->punch)
// 		punch(g);
// }

//it would be better to check for that in the main draw_vertical_line, because this is counting twice for one wall...
void	draw_wallcrack(t_game *g, int x, int wall_height)
{
	int				draw_start = -wall_height / 2 + S_HEIGHT / 2;
	int				draw_end = wall_height + draw_start;
	int	y;
	int	y_tx;
	double	y_proportion;
	unsigned int	x_tx;
	int	wall_color;

	if (draw_end > S_HEIGHT)
		draw_end = S_HEIGHT - 1;
	y_proportion = (((double) g->wallcrack->height / (double) wall_height));
	y_tx = 0;
	x_tx = 0;
	y = draw_start;
	if (draw_start < 0)
		y = 0;
	// printf("draw start %i y %i\n", draw_start, y);
	while (y < draw_end + 1)
	{
		// printf(ANSI_MAGENTA"wallheight %i\ndrawstart %i\n x %i\n y %i\n"ANSI_RESET, wall_height, draw_start, x, y);
		if ((y_tx + 3) <= (int)(g->wallcrack->width * g->wallcrack->height * 4)
			&& g->wallcrack->pixels[y_tx + 3] != 0)
		{
			wall_color = get_rgba(g->wallcrack->pixels[y_tx], g->wallcrack->pixels[y_tx + 1], 
					g->wallcrack->pixels[y_tx + 2], g->wallcrack->pixels[y_tx + 3]);
			mlx_put_pixel(g->bg, x, y, wall_color);
		}
		y++;
		y_tx = round((y - draw_start) * y_proportion);
		if (y_tx >= (int)g->wallcrack->height)
			y_tx = g->wallcrack->height - 1;
		y_tx *= g->wallcrack->width;
		x_tx = round(g->ray.x_intersect * g->wallcrack->width);
		if ((g->ray.hit_x_wall && g->ray.ray_dir.x < 0)
			|| (!g->ray.hit_x_wall && g->ray.ray_dir.y > 0))
			x_tx = round((1 - g->ray.x_intersect) * g->wallcrack->width);
		else
			x_tx = round(g->ray.x_intersect * g->wallcrack->width);
		if (x_tx >= g->wallcrack->width)
			x_tx = g->wallcrack->width - 1;
		y_tx += x_tx;
		y_tx *= 4;
	}
}

void	draw_vertical_line(t_game *g, int x)
{
	int				wall_height = (int)(S_HEIGHT / g->ray.perp_wall_dist);
	int				draw_start = -wall_height / 2 + S_HEIGHT / 2;
	int				draw_end = wall_height + draw_start;
	int				*wall_color;
int				ceiling_color = g->map.ceiling_color;
	int				floor_color = g->map.floor_color;
	int				y;
	double			y_proportion;
	int				y_tx;
	unsigned int	x_tx = 0;
	mlx_texture_t	*tex;

	if (draw_end > S_HEIGHT)
		draw_end = S_HEIGHT - 1;
	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(g->bg, x, y, ceiling_color);
		y++;
	}
	if (g->ray.hit_x_wall)
	{
		if (g->ray.ray_dir.x > 0)
		{
			// if (EASTER && g->mini_color && (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == 'D' || g->map.tiles[g->ray.tile_y][g->ray.tile_x] == 'd'))
			// if (EASTER && g->mini_color && (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == 'd'))
			// if (g->mini_img && g->mini_color && (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == 'd'))
			// {
			// 	// printf("EASTER");
			// 	tex = g->mini_tex;
			// 	wall_color = g->mini_color;
			// 	// g->mini_img = !g->mini_img;
			// }
			// else
			// {
				tex = g->textures.ea_tex;
				wall_color = g->textures.color_ea;
			// }
		}
		else
		{
			tex= g->textures.we_tex;
			wall_color = g->textures.color_we;
		}
	}
	else
	{
		if (g->ray.ray_dir.y > 0)
		{
			tex = g->textures.so_tex;
			wall_color = g->textures.color_so;
		}
		else
		{
			tex = g->textures.no_tex;
			wall_color = g->textures.color_no;
		}
	}
	y_proportion = (((double) tex->height / (double) wall_height));
	y_tx = 0;
	while (y < draw_end + 1)
	{
		if ((y_tx) <= (int)(tex->width * tex->height))
		{
			mlx_put_pixel(g->bg, x, y, wall_color[y_tx]);
		}
		y++;
		y_tx = round((y - draw_start) * y_proportion);
		if (y_tx >= (int)tex->height)
			y_tx = tex->height - 1;
		y_tx *= tex->width;
		x_tx = round(g->ray.x_intersect * tex->width);
		if ((g->ray.hit_x_wall && g->ray.ray_dir.x < 0)
			|| (!g->ray.hit_x_wall && g->ray.ray_dir.y > 0))
			x_tx = round((1 - g->ray.x_intersect) * tex->width);
		else
			x_tx = round(g->ray.x_intersect * tex->width);
		if (x_tx >= tex->width)
			x_tx = tex->width - 1;
		y_tx += x_tx;
	}
	
	if (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '2'
		|| g->map.tiles[g->ray.tile_y][g->ray.tile_x] == 'd')
		draw_wallcrack(g, x, wall_height);
	while (y < S_HEIGHT)
	{
		mlx_put_pixel(g->bg, x, y, floor_color);
		y++;
	}
	if (g->player.punch)
		punch(g);
}

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
	printf("\n\nmlx width %d height %d\nleft hand w %d h %d x %d y %d\nright hand w %d h %d x %d y %d\n", g->mlx->width, g->mlx->height, g->hands[1]->width, g->hands[1]->height, g->hands[1]->instances->x, g->hands[1]->instances->y, g->hands[0]->width, g->hands[0]->height, g->hands[0]->instances->x, g->hands[0]->instances->y);
	printf("looking at x_wall %d\n", g->player.look_x_wall);
	// 	while (map->copy[y])
	// {
	// 	printf("copy[%zu]:	'%s'\n", y, map->copy[y]);
	// 	y++;
	// }
}
