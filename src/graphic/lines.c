/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:51:37 by nsloniow          #+#    #+#             */
/*   Updated: 2025/05/06 14:02:37 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_line_to_bottom(t_game *game, double start_x,
			double start_y, double slope);
void	draw_line_to_left(t_game *game, double start_x, double start_y,
			double slope);
void	draw_line_to_right(t_game *game, double start_x, double start_y,
			double slope);
void	draw_line_to_top(t_game *game, double start_x, double start_y,
			double slope);
double	slope(double x_diff, double y_diff);

// y dominant
void	draw_line_to_bottom(t_game *game, double start_x, double start_y,
	double slope)
{
	double			x;
	double			y;
	t_cords_int32	yx;
	t_height_width	height_width;

	x = start_x;
	y = start_y;
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

// x dominant
void	draw_line_to_left(t_game *game, double start_x, double start_y,
	double slope)
{
	double			x;
	double			y;
	t_cords_int32	yx;
	t_height_width	height_width;

	x = start_x;
	y = start_y;
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

// x dominant
void	draw_line_to_right(t_game *game, double start_x, double start_y,
	double slope)
{
	double			x;
	double			y;
	t_cords_int32	yx;
	t_height_width	height_width;

	x = start_x;
	y = start_y;
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

// y dominant
void	draw_line_to_top(t_game *game, double start_x, double start_y,
	double slope)
{
	double			x;
	double			y;
	t_cords_int32	yx;
	t_height_width	height_width;

	x = start_x;
	y = start_y;
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

double	slope(double x_diff, double y_diff)
{
	double	slope;

	if (x_diff == 0)
		slope = 0;
	else
		slope = y_diff / x_diff;
	return (slope);
}
