/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/04/10 14:50:41 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
void			draw_mini_map(t_game *game);
static double	slope(double x_diff, double y_diff);

void	draw_mini_fov(t_game *game)
{
	double	miniplayer_x;
	double	miniplayer_y;
	int		lines_per_side_off_direction_line;

    miniplayer_x = game->player.pos.x * MINI_UNITS_PER_TILE
					* MINI_RESIZE_FACTOR;
    miniplayer_y = game->player.pos.y * MINI_UNITS_PER_TILE
					* MINI_RESIZE_FACTOR;
    // draw cone
	// calculate Ampunt of Lines depending on fov angle and angle of lines next
	// to each other
	lines_per_side_off_direction_line = -(FOV / ANGLE_SPREAD) / 2;
	// half on the left side, half on the right side
    while ( lines_per_side_off_direction_line <= (FOV / ANGLE_SPREAD) / 2 )
    {
        // Calculate the new angle for each cone line
        double angle = atan2(game->player.dir.y, game->player.dir.x) +
						( lines_per_side_off_direction_line * ANGLE_SPREAD);
        // Calculate the direction vector for this new angle
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
        pixset_yx_height_width(game->minimap, get_rgba(R, G, B, A), yx,
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
		pixset_yx_height_width(game->minimap, get_rgba(R, G, B, A), yx,
								height_width);
		x--;
	}

}