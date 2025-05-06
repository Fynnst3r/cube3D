/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minifov.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:08:01 by nsloniow          #+#    #+#             */
/*   Updated: 2025/05/06 14:14:37 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	clear_mini_fov_img(t_game *game, t_cords_int32 yx);
void	draw_fov_direction_line(t_game *game);
void	draw_mini_fov(t_game *game);

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
