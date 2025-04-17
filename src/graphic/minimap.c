/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/04/17 18:58:47 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void			clear_img(mlx_image_t *img);
void			draw_fov_direction_line(t_game *game);
static void		draw_line_to_right(t_game *game, double start_x, double start_y,
									double slope);
static void		draw_line_to_left(t_game *game, double start_x, double start_y,
									double slope);
static void		draw_line_to_bottom(t_game *game, double start_x, double start_y,
									double slope);
static void		draw_line_to_top(t_game *game, double start_x, double start_y,
									double slope);
void			draw_mini_fov(t_game *game);
static void		draw_minimap_tile(t_game *game, size_t y, size_t x,
									t_height_width hw);
void			init_minimap(t_game *game);
void			save_pixels_for_reinstate(t_game *game);
static double	slope(double x_diff, double y_diff);
void			minimap_change(t_game *game);

void	clear_img(mlx_image_t *img)
{
	u_int32_t	y;
	u_int32_t	x;

	y = 0;
	x = 0;
	while (y < img->height)
	{
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, get_rgba(255, 255, 255, 255)); // fully transparent
			pixset(img, get_rgba(22,222, 222,225));
			x++;
		}
		y++;
	}
}
void	save_pixels_for_reinstate(t_game *game)
{
	u_int32_t	y;
	u_int32_t	x;

	y = 0;
	x = 0;
	// game->mini_previouse_pixels = mlx_new_image(game->mlx, game->mini_previouse_pixels);

	while (y < game->minimap->height)
	{
		while (x < game->minimap->width)
		{
			// pixset(img, get_rgba(22,222, 222,225));
			// game->mini_previouse_pixels.pixels[x];
			x++;
		}
		y++;
	}
}

void	draw_mini_fov(t_game *game)
{
	double	miniplayer_x;
	double	miniplayer_y;
	int		lines_per_side_off_direction_line;
	t_cords_int32	yx;
	t_height_width	height_width;

	yx.x = 0;
	yx.y = 0;
	height_width.height = game->minimap->height;
	height_width.width = game->minimap->width;
	pixset_yx_height_width(game->minifov, 0 , yx, height_width);
    miniplayer_x = game->player.pos.x * MINI_UNITS_PER_TILE
					* MINI_RESIZE_FACTOR;
    miniplayer_y = game->player.pos.y * MINI_UNITS_PER_TILE
					* MINI_RESIZE_FACTOR;
	lines_per_side_off_direction_line = -(FOV / ANGLE_SPREAD) / 2;
    while ( lines_per_side_off_direction_line <= (FOV / ANGLE_SPREAD) / 2 )
    {
        double angle = atan2(game->player.dir.y, game->player.dir.x) +
						( lines_per_side_off_direction_line * ANGLE_SPREAD);
        game->fov_line_end_x = miniplayer_x + cos(angle) * MINI_RAY_LENGRH
								* MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
        game->fov_line_end_y = miniplayer_y + sin(angle) * MINI_RAY_LENGRH
								* MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
        draw_fov_direction_line(game);
		lines_per_side_off_direction_line++;
    }
}

// x dominant
static void draw_line_to_right(t_game *game, double start_x, double start_y,
								double slope)
{
    double x = start_x;
    double y = start_y;
    t_cords_int32 yx;
    t_height_width height_width;

    height_width.height = MINI_LINE_HEIGHT;
    height_width.width = MINI_LINE_WIDTH;
    while (x <= game->fov_line_end_x)
    {
        y = round(slope * (x - start_x) + start_y);
        yx.x = (int32_t)x;
        yx.y = (int32_t)y;
        pixset_yx_height_width(game->minifov, get_rgba(R, G, B, A), yx,
								height_width);
        x++;
    }
}

// x dominant
static void draw_line_to_left(t_game *game, double start_x, double start_y,
								double slope)
{
    double x = start_x;
    double y = start_y;
    t_cords_int32 yx;
    t_height_width height_width;

    height_width.height = MINI_LINE_HEIGHT;
    height_width.width = MINI_LINE_WIDTH;
	while (x >= game->fov_line_end_x)
	{
		y = round(slope * (x - start_x) + start_y);
		
		yx.x = (int32_t)x;
		yx.y = (int32_t)y;
		pixset_yx_height_width(game->minifov, get_rgba(R, G, B, A), yx,
								height_width);
		x--;
	}

}

// y dominant
static void	draw_line_to_bottom(t_game *game, double start_x, double start_y,
								double slope)
{
	double x = start_x;
	double y = start_y;
	t_cords_int32 yx;
	t_height_width height_width;

	height_width.height = MINI_LINE_HEIGHT;
	height_width.width = MINI_LINE_WIDTH;
	while (y <= game->fov_line_end_y)
	{
		x = round(slope * (y - start_y) + start_x);
		yx.x = (int32_t)x;
		yx.y = (int32_t)y;
		pixset_yx_height_width(game->minifov, get_rgba(R, G, B, A), yx,
								height_width);
		y++;
	}
}

// y dominant
static void	draw_line_to_top(t_game *game, double start_x, double start_y,
								double slope)
{
	double x = start_x;
	double y = start_y;
	t_cords_int32 yx;
	t_height_width height_width;

	height_width.height = MINI_LINE_HEIGHT;
	height_width.width = MINI_LINE_WIDTH;
	while (y >= game->fov_line_end_y)
	{
		x = round(slope * (y - start_y) + start_x);
		yx.x = (int32_t)x;
		yx.y = (int32_t)y;
		pixset_yx_height_width(game->minifov, get_rgba(R, G, B, A), yx,
								height_width);
		y--;
	}
}
static double	slope(double x_diff, double y_diff)
{
	double	slope;
	if (x_diff == 0)
		slope = 0;
	else
		slope = y_diff / x_diff;
	return (slope);
}

void	draw_fov_direction_line(t_game *game)
{
	t_cords			start;
	t_height_width	height_width;
	double			x_diff;
	double			y_diff;
		
	start.x = game->player.pos.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	start.y = game->player.pos.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	height_width.height = MINI_LINE_HEIGHT;
	height_width.width = MINI_LINE_WIDTH;
	x_diff = game->fov_line_end_x - start.x;
	y_diff = game->fov_line_end_y - start.y;
	// if (fabs(x_diff) >= fabs(y_diff))
	if (fabs(x_diff) > fabs(y_diff))
	{
		if (x_diff > 0)
			draw_line_to_right(game, start.x, start.y, slope(x_diff, y_diff));
		// if (x_diff < 0)
		if (x_diff <= 0)
			draw_line_to_left(game, start.x, start.y, slope(x_diff, y_diff));
	}
	else
	{
		if (y_diff > 0)
			draw_line_to_bottom(game, start.x, start.y, slope(y_diff, x_diff));
		// if (y_diff < 0)
		if (y_diff <= 0)
			draw_line_to_top(game, start.x, start.y, slope(y_diff, x_diff));
	}
}

static void	draw_minimap_tile(t_game *game, size_t y, size_t x,
								t_height_width hw)
{
	t_cords_int32	yx;

	yx.y = y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	yx.x = x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	if (game->map.tiles[y][x] != '0' && game->map.tiles[y][x] != ' ')
	{
		// printf("%s %d game->map.tiles[y][x] %s\n", __FILE__, __LINE__, game->map.tiles[y][x]);
		pixset_yx_height_width(game->minifov, 0, yx, hw);
		pixset_yx_height_width(game->minimap, get_rgba(0, 77, 77, 255), yx, hw);
		if(game->map.tiles[y][x] == 'D')
			pixset_yx_height_width(game->minimap, get_rgba(33, 166, 188, 255), yx, hw);
		if(game->map.tiles[y][x] == 'd')
			pixset_yx_height_width(game->minimap, get_rgba(244, 11, 88, 255), yx, hw);
	}
	else if (game->map.tiles[y][x] == '0')
	{
		pixset_yx_height_width(game->minifov, 0, yx, hw);
		pixset_yx_height_width(game->minimap, get_rgba(0, 255, 255, 255), yx, hw);
	}
}

void	init_minimap(t_game *game)
{
	size_t	y;
	size_t	x;
	// t_cords_int32	yx;
	t_height_width	height_width;

	height_width.height = MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	height_width.width = MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	y = 0;
	x = 0;
	game->minimap = mlx_new_image(game->mlx,
					game->map.max_x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR,
					game->map.max_y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR);
	game->minifov = mlx_new_image(game->mlx,
						game->map.max_x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR,
						game->map.max_y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR);
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
	// if (mlx_image_to_window(game->mlx, game->minimap,0,0) < 0)
	// {
	// 	ft_error("Error\nImage didn't arrive at window", 1, game);
	// }
	// if max size bigger 100 / 10 if bigger 1000 / 100...
	// mlx_resize_image(game->minimap, game->bg->width/MINI_RESIZE_FACTOR,
	// 	game->bg->height/MINI_RESIZE_FACTOR);
	// mlx_resize_image(game->minimap, game->minimap->width * MINI_RESIZE_FACTOR,
	// 	game->minimap->height * MINI_RESIZE_FACTOR);
}

void	minimap_change(t_game *game)
{
	size_t	y;
	size_t	x;
	t_cords_int32	yx;
	t_height_width	height_width;
	height_width.height = MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	height_width.width = MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	y = 0;
	x = 0;
	// game->minimap = mlx_new_image(game->mlx,
	// 				game->map.max_x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR,
	// 				game->map.max_y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR);					
	while (game->map.tiles[y] != NULL)
	{
		while (game->map.tiles[y][x] != 0)
		{	
			// printf("%s %d game->map.tiles[y][x] %s\n", __FILE__, __LINE__, game->map.tiles[y][x]);
			// draw_minimap_tile(game, y, x, height_width);
			if(game->map.tiles[y][x] == 'D')
			{
				yx.y = y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
				yx.x = x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
				pixset_yx_height_width(game->minimap, get_rgba(33, 166, 188, 255), yx, height_width);
			}
			if(game->map.tiles[y][x] == 'd')
			{
				yx.y = y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
				yx.x = x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
				pixset_yx_height_width(game->minimap, get_rgba(244, 11, 88, 255), yx, height_width);
			}
			if(game->map.tiles[y][x] == '0')
			{
				yx.y = y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
				yx.x = x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
				pixset_yx_height_width(game->minimap, get_rgba(0, 255, 255, 255), yx, height_width);
			}
			x += 1;
		}
		x = 0;
		y += 1;
	}
	// game->minimap_drawn = false;
	// game->show_minimap = false;
	// game->minifov->enabled = false;
	// game->minimap->enabled = false;
	// if (mlx_image_to_window(game->mlx, game->minimap, 0, 0) < 0)
		// ft_error("Error\nImage didn't arrive at window", 1, game);
	// if (mlx_image_to_window(game->mlx, game->minifov, 0, 0) < 0)
		// ft_error("Error\nImage didn't arrive at window", 1, game);
	// if (mlx_image_to_window(game->mlx, game->minimap,0,0) < 0)
	// {
	// 	ft_error("Error\nImage didn't arrive at window", 1, game);
	// }
	// if max size bigger 100 / 10 if bigger 1000 / 100...
	// mlx_resize_image(game->minimap, game->bg->width/MINI_RESIZE_FACTOR,
	// 	game->bg->height/MINI_RESIZE_FACTOR);
	// mlx_resize_image(game->minimap, game->minimap->width * MINI_RESIZE_FACTOR,
	// 	game->minimap->height * MINI_RESIZE_FACTOR);
}