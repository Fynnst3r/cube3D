/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:28:11 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 18:28:38 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	walk_forward(char **tiles, t_cords *pos, t_cords *dir, double mv_speed)
{
	double	next_x;
	double	next_y;

	next_x = pos->x + dir->x * mv_speed;
	next_y = pos->y + dir->y * mv_speed;
	if (tiles[(size_t)(pos->y)][(size_t)(next_x)] == '0')
		pos->x += dir->x * mv_speed;
	if (tiles[(size_t)(next_y)][(size_t)pos->x] == '0')
		pos->y += dir->y * mv_speed;
}

void	walk_backwards(char **tiles, t_cords *pos, t_cords *dir
	, double mv_speed)
{
	double	next_x_rev;
	double	next_y_rev;

	next_x_rev = pos->x - dir->x * mv_speed;
	next_y_rev = pos->y - dir->y * mv_speed;
	if (tiles[(size_t)(pos->y)][(size_t)(next_x_rev)] == '0')
		pos->x -= dir->x * mv_speed;
	if (tiles[(size_t)(next_y_rev)][(size_t)pos->x] == '0')
		pos->y -= dir->y * mv_speed;
}

void	strafe_left(char **tiles, t_cords *pos, t_cords *dir, double mv_speed)
{
	double	next_x_plane_left;
	double	next_y_plane_left;

	next_x_plane_left = pos->x + dir->y * mv_speed;
	next_y_plane_left = pos->y - dir->x * mv_speed;
	if (tiles[(size_t)(pos->y)][(size_t)(next_x_plane_left)] == '0')
		pos->x += dir->y * mv_speed;
	if (tiles[(size_t)(next_y_plane_left)][(size_t)pos->x] == '0')
		pos->y -= dir->x * mv_speed;
}

void	strafe_right(char **tiles, t_cords *pos, t_cords *dir, double mv_speed)
{
	double	next_x_plane_right;
	double	next_y_plane_right;

	next_x_plane_right = pos->x - dir->y * mv_speed;
	next_y_plane_right = pos->y + dir->x * mv_speed;
	if (tiles[(size_t)(pos->y)][(size_t)(next_x_plane_right)] == '0')
		pos->x -= dir->y * mv_speed;
	if (tiles[(size_t)(next_y_plane_right)][(size_t)pos->x] == '0')
		pos->y += dir->x * mv_speed;
}

void	rotate_player(t_cords *dir, t_cords *plane, double rt_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = dir->x;
	dir->x = dir->x * cos(rt_speed) - dir->y * sin(rt_speed);
	dir->y = old_dir_x * sin(rt_speed) + dir->y * cos(rt_speed);
	old_plane_x = plane->x;
	plane->x = plane->x * cos(rt_speed) - plane->y * sin(rt_speed);
	plane->y = old_plane_x * sin(rt_speed) + plane->y * cos(rt_speed);
}
