/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:57 by fforster          #+#    #+#             */
/*   Updated: 2025/03/10 17:14:16 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// int	oob(t_game g, size_t y, size_t x)
// {
// 	if (g.map.max_x - 1 < x || g.map.max_y - 1 < y)
// 		return (1);
// 	return (0);
// }

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

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game			*g;

	g = (t_game *)param;
	double	rt_speed = g->mlx->delta_time * RT_SPEED;
	double	mv_speed = g->mlx->delta_time * MV_SPEED;
	// double	rt_speed = g->mlx->delta_time * RT_SPEED;
	// double	mv_speed = 0.12;
	// printf("mv_speed %f\n rt_speed %f\n", mv_speed, rt_speed);

	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(g->mlx);
		ft_error("Game closed with esc.\n", 0, g);
	}
	print_ray_status(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		// printf(ANSI_RED"next y %f\n"ANSI_RESET, next_y);
		// printf(ANSI_RED"next x %f\n"ANSI_RESET, next_x);
		// printf(ANSI_RED"next INT x %d\n"ANSI_RESET, (int)(g->player.pos.x + g->player.dir.x * mv_speed));
		walk_forward(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		walk_backwards(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		strafe_left(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		strafe_right(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = g->player.dir.x;
		g->player.dir.x = g->player.dir.x * cos(rt_speed) - g->player.dir.y * sin(rt_speed);
		g->player.dir.y = oldDirX * sin(rt_speed) + g->player.dir.y * cos(rt_speed);
		double oldPlaneX = g->ray.plane.x;
		g->ray.plane.x = g->ray.plane.x * cos(rt_speed) - g->ray.plane.y * sin(rt_speed);
		g->ray.plane.y = oldPlaneX * sin(rt_speed) + g->ray.plane.y * cos(rt_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = g->player.dir.x;
		g->player.dir.x = g->player.dir.x * cos(-rt_speed) - g->player.dir.y * sin(-rt_speed);
		g->player.dir.y = oldDirX * sin(-rt_speed) + g->player.dir.y * cos(-rt_speed);
		double oldPlaneX = g->ray.plane.x;
		g->ray.plane.x = g->ray.plane.x * cos(-rt_speed) - g->ray.plane.y * sin(-rt_speed);
		g->ray.plane.y = oldPlaneX * sin(-rt_speed) + g->ray.plane.y * cos(-rt_speed);
	}
	// printf(ANSI_GREEN"pos x %f, pos y %f\n", game->player.pos.x, game->player.pos.y);
	// printf("PLAYERdir x %f - PLAYERdir y %f\n"ANSI_RESET, game->player.dir.x, game->player.dir.y);
}
