/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:09:26 by nsloniow          #+#    #+#             */
/*   Updated: 2025/05/08 16:50:35 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_pixel_from_tex(t_game *g, unsigned int x, mlx_texture_t *tex,
			int *wall_color);
void	draw_wallcrack(t_game *g, int x, int wall_height);
int		get_x_of_texture(t_game *game, uint32_t tex_width);
void	print_ray_status(t_game *g);
void	select_wall_texture(t_game *g, mlx_texture_t **tex, int **wall_color);

void	draw_wallcrack(t_game *g, int x, int wall_height)
{
	int				y;
	int				y_tx;
	double			y_proportion;

	if (g->ray.draw_end > S_HEIGHT)
		g->ray.draw_end = S_HEIGHT - 1;
	y_proportion = (((double) g->wallcrack->height / (double) wall_height));
	y_tx = 0;
	y = g->ray.draw_start;
	if (g->ray.draw_start < 0)
		y = 0;
	while (y < g->ray.draw_end + 1)
	{
		if ((y_tx + 3) <= (int)(g->wallcrack->width * g->wallcrack->height * 4)
			&& g->wallcrack->pixels[y_tx + 3] != 0)
			mlx_put_pixel(g->bg, x, y, get_rgba(g->wallcrack->pixels[y_tx],
					g->wallcrack->pixels[y_tx + 1],
					g->wallcrack->pixels[y_tx + 2],
					g->wallcrack->pixels[y_tx + 3]));
		y_tx = round((++y - g->ray.draw_start) * y_proportion);
		if (y_tx >= (int)g->wallcrack->height)
			y_tx = g->wallcrack->height - 1;
		y_tx = ((y_tx * g->wallcrack->width)
				+ get_x_of_texture(g, g->wallcrack->width)) * 4;
	}
}

void	select_wall_texture(t_game *g, mlx_texture_t **tex, int **wall_color)
{
	if (g->ray.hit_x_wall)
	{
		if (g->ray.ray_dir.x > 0)
		{
			*tex = g->textures.ea_tex;
			*wall_color = g->textures.color_ea;
		}
		else
		{
			*tex = g->textures.we_tex;
			*wall_color = g->textures.color_we;
		}
		return ;
	}
	if (g->ray.ray_dir.y > 0)
	{
		*tex = g->textures.so_tex;
		*wall_color = g->textures.color_so;
	}
	else
	{
		*tex = g->textures.no_tex;
		*wall_color = g->textures.color_no;
	}
}

int	get_x_of_texture(t_game *game, uint32_t tex_width)
{
	unsigned int	x_tex;

	x_tex = round(game->ray.x_intersect * tex_width);
	if ((game->ray.hit_x_wall && game->ray.ray_dir.x < 0)
		|| (!game->ray.hit_x_wall && game->ray.ray_dir.y > 0))
		x_tex = round((1 - game->ray.x_intersect) * tex_width);
	else
		x_tex = round(game->ray.x_intersect * tex_width);
	if (x_tex >= tex_width)
		x_tex = tex_width - 1;
	return (x_tex);
}

void	draw_pixel_from_tex(t_game *g, unsigned int x, mlx_texture_t *tex,
	int *wall_color)
{
	int				y_tex;
	unsigned int	x_tex;
	int				y;
	double			y_proportion;

	y_tex = 0;
	y = g->ray.draw_start;
	if (g->ray.draw_start < 0)
		y = 0;
	y_proportion = (((double) tex->height / (double) g->ray.wall_height));
	while (y < g->ray.draw_end + 1)
	{
		if (y_tex >= 0 && (y_tex) < (int)(tex->width * tex->height))
			mlx_put_pixel(g->bg, x, y, wall_color[y_tex]);
		y++;
		y_tex = round((y - g->ray.draw_start) * y_proportion);
		if (y_tex >= (int)tex->height)
			y_tex = tex->height - 1;
		y_tex *= tex->width;
		x_tex = get_x_of_texture(g, tex->width);
		y_tex += x_tex;
	}
}

void	draw_vertical_line(t_game *g, int x)
{
	int				*wall_color;
	int				y;
	mlx_texture_t	*tex;

	g->ray.wall_height = (int)(S_HEIGHT / g->ray.perp_wall_dist);
	g->ray.draw_start = -g->ray.wall_height / 2 + S_HEIGHT / 2;
	g->ray.draw_end = g->ray.wall_height + g->ray.draw_start;
	wall_color = NULL;
	tex = NULL;
	if (g->ray.draw_end > S_HEIGHT)
		g->ray.draw_end = S_HEIGHT - 1;
	y = -1;
	while (++y < g->ray.draw_start)
		mlx_put_pixel(g->bg, x, y, g->map.ceiling_color);
	select_wall_texture(g, &tex, &wall_color);
	draw_pixel_from_tex(g, x, tex, wall_color);
	if (g->map.tiles[g->ray.tile_y][g->ray.tile_x] == '2'
		|| g->map.tiles[g->ray.tile_y][g->ray.tile_x] == 'd')
		draw_wallcrack(g, x, g->ray.wall_height);
	y = g->ray.draw_end;
	while (++y < S_HEIGHT)
		mlx_put_pixel(g->bg, x, y, g->map.floor_color);
	if (g->player.punch)
		punch(g);
}


//prints various info of the state of the ray for debug
void	print_ray_status(t_game *g)
{
	printf(ANSI_GREEN"PLAYER y %f - PLAYER x %f\n"ANSI_RESET, g->player.pos.y,
		g->player.pos.x);
	printf("PLAYERdir x %f - PLAYERdir y %f\n", g->player.dir.x,
		g->player.dir.y);
	printf("plane x %f - plane y %f\n", g->ray.plane.x, g->ray.plane.y);
	printf("camera x %f\n", g->ray.camera_x);
	printf(ANSI_BLUE"ray tile x %zu - y %zu\n"ANSI_RESET, g->ray.tile_x,
		g->ray.tile_y);
	printf("ray_dir x %f - ray_dir y %f\n", g->ray.ray_dir.x, g->ray.ray_dir.y);
	printf(ANSI_YELLOW"side_dist x %f - side_dist y %f\n"ANSI_RESET,
		g->ray.side_dist.x, g->ray.side_dist.y);
	printf(ANSI_MAGENTA"delta_dist x %f - delta_dist y %f\n"ANSI_RESET,
		g->ray.delta_dist.x, g->ray.delta_dist.y);
	printf("perpendicular_wall_dist %f\n", g->ray.perp_wall_dist);
	printf("go x %i, go y %i\n\n", g->ray.go_x, g->ray.go_y);
	// printf("\n\nmlx width %d height %d\nleft hand w %d h %d x %d y %d\n
	// 	right hand w %d h %d x %d y %d\n", g->mlx->width, g->mlx->height,
	// 	g->hands[1]->width, g->hands[1]->height, g->hands[1]->instances->x,
	// 	g->hands[1]->instances->y, g->hands[0]->width, g->hands[0]->height,
	// 	g->hands[0]->instances->x, g->hands[0]->instances->y);
	printf("looking at x_wall %d\n", g->player.look_x_wall);
}