/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/05/06 15:18:29 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_tile_on_change(t_game *game, size_t y,
			size_t x, t_height_width height_width);
void	draw_minimap_tile(t_game *game, size_t y, size_t x,
			t_height_width height_width);
void	init_minimap(t_game *game);
void	mini_img_for_resize_factor(t_game *game,
			t_height_width *height_width);
void	minimap_change(t_game *game);

void	draw_tile_on_change(t_game *game, size_t y, size_t x,
	t_height_width height_width)
{
	t_cords_int32	yx;

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
}

void	draw_minimap_tile(t_game *game, size_t y, size_t x,
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
		if (game->map.tiles[y][x] == 'D')
			pixset_yx_height_width(game->minimap, get_rgba(33, 166, 188, 255),
				yx, height_width);
		if (game->map.tiles[y][x] == 'd')
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
	height_width.height = 0;
	height_width.width = 0;
	mini_img_for_resize_factor(game, &height_width);
	while (game->map.tiles[y] != NULL)
	{
		x = -1;
		while (game->map.tiles[y][++x] != 0)
			draw_minimap_tile(game, y, x, height_width);
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

void	mini_img_for_resize_factor(t_game *game,
	t_height_width *height_width)
{
	game->mini_resize_factor = MINI_RESIZE_FACTOR;
	if (game->map.max_x * MINI_UNITS_PER_TILE * game->mini_resize_factor
		> S_WIDTH)
		game->mini_resize_factor = (double)S_WIDTH / (game->map.max_x
				* MINI_UNITS_PER_TILE);
	if (game->map.max_y * MINI_UNITS_PER_TILE * game->mini_resize_factor
		> S_HEIGHT)
		game->mini_resize_factor = (double)S_HEIGHT / (game->map.max_y
				* MINI_UNITS_PER_TILE);
	height_width->height = MINI_UNITS_PER_TILE * game->mini_resize_factor;
	height_width->width = MINI_UNITS_PER_TILE * game->mini_resize_factor;
	game->minimap = mlx_new_image(game->mlx,
			game->map.max_x * height_width->width,
			game->map.max_y * height_width->height);
	game->minifov = mlx_new_image(game->mlx,
			game->map.max_x * height_width->width,
			game->map.max_y * height_width->height);
}

void	minimap_change(t_game *game)
{
	size_t			y;
	size_t			x;
	t_height_width	height_width;

	y = 0;
	x = 0;
	height_width.height = MINI_UNITS_PER_TILE * game->mini_resize_factor;
	height_width.width = MINI_UNITS_PER_TILE * game->mini_resize_factor;
	while (game->map.tiles[y] != NULL)
	{
		while (game->map.tiles[y][x] != 0)
		{
			draw_tile_on_change(game, y, x, height_width);
			x += 1;
		}
		x = 0;
		y += 1;
	}
}
