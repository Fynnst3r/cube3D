/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:09:26 by nsloniow          #+#    #+#             */
/*   Updated: 2025/05/08 16:34:34 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_pixel_from_tex(t_game *g, unsigned int x, mlx_texture_t *tex,
			int *wall_color);
void	draw_wallcrack(t_game *g, int x, int wall_height);
int		get_x_of_texture(t_game *game, uint32_t tex_width);
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
