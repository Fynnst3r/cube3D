/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/05/06 13:34:14 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void			clear_mini_fov_img(t_game *game, t_cords_int32 yx);
void			draw_fov_direction_line(t_game *game);
void			draw_mini_fov(t_game *game);
static void		draw_minimap_tile(t_game *game, size_t y, size_t x,
					t_height_width hw);
void			init_minimap(t_game *game);
void			minimap_change(t_game *game);

void	clear_mini_fov_img(t_game *game, t_cords_int32 yx)
{
	t_height_width	height_width;

	height_width.height = game->minimap->height;
	height_width.width = game->minimap->width;
	pixset_yx_height_width(game->minifov, 0, yx, height_width);
}

void	draw_mini_fov(t_game *game)
{
	t_miniplayer	miniplayer;
	int				lines_per_side_of_direction_line;
	t_cords_int32	yx;
	double			angle;

	yx.x = 0;
	yx.y = 0;
	clear_mini_fov_img(game, yx);
	miniplayer.x = game->player.pos.x * MINI_UNITS_PER_TILE
		* game->mini_resize_factor;
	miniplayer.y = game->player.pos.y * MINI_UNITS_PER_TILE
		* game->mini_resize_factor;
	lines_per_side_of_direction_line = -(FOV / ANGLE_SPREAD) / 2;
	while (lines_per_side_of_direction_line <= (FOV / ANGLE_SPREAD) / 2)
	{
		angle = atan2(game->player.dir.y, game->player.dir.x)
			+ (lines_per_side_of_direction_line * ANGLE_SPREAD);
		game->fov_line_end_x = miniplayer.x + cos(angle) * MINI_RAY_LENGRH
			* MINI_UNITS_PER_TILE * game->mini_resize_factor;
		game->fov_line_end_y = miniplayer.y + sin(angle) * MINI_RAY_LENGRH
			* MINI_UNITS_PER_TILE * game->mini_resize_factor;
		draw_fov_direction_line(game);
		lines_per_side_of_direction_line++;
	}
}

void	draw_fov_direction_line(t_game *game)
{
	t_cords	start;
	double	x_diff;
	double	y_diff;

	start.x = game->player.pos.x * MINI_UNITS_PER_TILE
		* game->mini_resize_factor;
	start.y = game->player.pos.y * MINI_UNITS_PER_TILE
		* game->mini_resize_factor;
	x_diff = game->fov_line_end_x - start.x;
	y_diff = game->fov_line_end_y - start.y;
	if (fabs(x_diff) > fabs(y_diff))
	{
		if (x_diff > 0)
			draw_line_to_right(game, start.x, start.y, slope(x_diff, y_diff));
		if (x_diff <= 0)
			draw_line_to_left(game, start.x, start.y, slope(x_diff, y_diff));
	}
	else
	{
		if (y_diff > 0)
			draw_line_to_bottom(game, start.x, start.y, slope(y_diff, x_diff));
		if (y_diff <= 0)
			draw_line_to_top(game, start.x, start.y, slope(y_diff, x_diff));
	}
}

static void	draw_minimap_tile(t_game *game, size_t y, size_t x,
	t_height_width height_width)
{
	t_cords_int32	yx;

	yx.y = y * MINI_UNITS_PER_TILE * game->mini_resize_factor;
	yx.x = x * MINI_UNITS_PER_TILE * game->mini_resize_factor;
	if (game->map.tiles[y][x] != '0' && game->map.tiles[y][x] != ' ')
	{
		pixset_yx_height_width(game->minifov, 0, yx, height_width);
		pixset_yx_height_width(game->minimap, get_rgba(0, 77, 77, 255), yx,
			height_width);
		if(game->map.tiles[y][x] == 'D')
			pixset_yx_height_width(game->minimap, get_rgba(33, 166, 188, 255),
				yx, height_width);
		if(game->map.tiles[y][x] == 'd')
			pixset_yx_height_width(game->minimap, get_rgba(111, 222, 0, 255),
				yx, height_width);
	}
	else if (game->map.tiles[y][x] == '0')
	{
		pixset_yx_height_width(game->minifov, 0, yx, height_width);
		pixset_yx_height_width(game->minimap, get_rgba(122, 255, 255, 255), yx,
			height_width);
	}
}

void	init_minimap(t_game *game)
{
	size_t			y;
	size_t			x;
	t_height_width	height_width;

	y = 0;
	x = 0;
	game->mini_resize_factor = MINI_RESIZE_FACTOR;
	if (game->map.max_x * MINI_UNITS_PER_TILE * game->mini_resize_factor
			> S_WIDTH)
		game->mini_resize_factor = S_WIDTH / (game->map.max_x
			* MINI_UNITS_PER_TILE);
	if (game->map.max_y * MINI_UNITS_PER_TILE * game->mini_resize_factor
			> S_HEIGHT)
		game->mini_resize_factor = (double)S_HEIGHT / (double)(game->map.max_y
			* MINI_UNITS_PER_TILE);
	height_width.height = MINI_UNITS_PER_TILE * game->mini_resize_factor;
	height_width.width = MINI_UNITS_PER_TILE * game->mini_resize_factor;
	game->minimap = mlx_new_image(game->mlx,
			game->map.max_x * MINI_UNITS_PER_TILE * game->mini_resize_factor,
			game->map.max_y * MINI_UNITS_PER_TILE * game->mini_resize_factor);
	game->minifov = mlx_new_image(game->mlx,
			game->map.max_x * MINI_UNITS_PER_TILE * game->mini_resize_factor,
			game->map.max_y * MINI_UNITS_PER_TILE * game->mini_resize_factor);
	while (game->map.tiles[y] != NULL)
	{
		while (game->map.tiles[y][x] != 0)
		{
			draw_minimap_tile(game, y, x, height_width);
			x += 1;
		}
		x = 0;
		y += 1;
	}
	if (mlx_image_to_window(game->mlx, game->minimap, 0, 0) < 0)
		ft_error("Error\nImage didn't arrive at window", 1, game);
	if (mlx_image_to_window(game->mlx, game->minifov, 0, 0) < 0)
		ft_error("Error\nImage didn't arrive at window", 1, game);
	game->minimap_drawn = false;
	game->show_minimap = false;
	game->minifov->enabled = false;
	game->minimap->enabled = false;
	
}

void	minimap_change(t_game *game)
{
	size_t			y;
	size_t			x;
	t_cords_int32	yx;
	t_height_width	height_width;

	y = 0;
	x = 0;
	height_width.height = MINI_UNITS_PER_TILE * game->mini_resize_factor;
	height_width.width = MINI_UNITS_PER_TILE * game->mini_resize_factor;
	while (game->map.tiles[y] != NULL)
	{
		while (game->map.tiles[y][x] != 0)
		{
			if (game->map.tiles[y][x] == 'D')
			{
				yx.y = y * MINI_UNITS_PER_TILE * game->mini_resize_factor;
				yx.x = x * MINI_UNITS_PER_TILE * game->mini_resize_factor;
				pixset_yx_height_width(game->minimap,
					get_rgba(33, 166, 188, 255), yx, height_width);
			}
			if (game->map.tiles[y][x] == 'd')
			{
				yx.y = y * MINI_UNITS_PER_TILE * game->mini_resize_factor;
				yx.x = x * MINI_UNITS_PER_TILE * game->mini_resize_factor;
				pixset_yx_height_width(game->minimap,
					get_rgba(111, 222, 0, 255), yx, height_width);
			}
			if (game->map.tiles[y][x] == '0')
			{
				yx.y = y * MINI_UNITS_PER_TILE * game->mini_resize_factor;
				yx.x = x * MINI_UNITS_PER_TILE * game->mini_resize_factor;
				pixset_yx_height_width(game->minimap,
					get_rgba(122, 255, 255, 255), yx, height_width);
			}
			x += 1;
		}
		x = 0;
		y += 1;
	}
}
