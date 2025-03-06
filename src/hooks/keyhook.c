/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:57 by fforster          #+#    #+#             */
/*   Updated: 2025/03/04 13:09:02 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// void	move_player(t_game *g, float y, float x)
// {
// 	g->img->instances->y += y;
// 	g->img->instances->x += x;
// }

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	double	rt_speed = g->mlx->delta_time * RT_SPEED;
	double	mv_speed = g->mlx->delta_time * MV_SPEED;
	double	next_x = g->player.pos.x + g->player.dir.x * mv_speed;
	double	next_y = g->player.pos.y + g->player.dir.y * mv_speed;
	printf("mv_speed %f\n", mv_speed);
	printf("rt_speed %f\n", rt_speed);
	if (keydata.key == MLX_KEY_ESCAPE)
	{
//<<<<<<< fforster
		mlx_close_window(g->mlx);
		ft_error("Game closed with esc.\n", 0, g);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		// print_ray_status(g);
		// printf(ANSI_RED"next y %f\n"ANSI_RESET, next_y);
		// printf(ANSI_RED"next x %f\n"ANSI_RESET, next_x);
		// printf(ANSI_RED"next INT x %d\n"ANSI_RESET, (int)(g->player.pos.x + g->player.dir.x * mv_speed));
		if (g->map.tiles[(int)(next_y)][(int)g->player.pos.x] == '0')
			g->player.pos.x += g->player.dir.x * mv_speed;
		if (g->map.tiles[(int)(g->player.pos.y)][(int)(next_x)] == '0')
			g->player.pos.y += g->player.dir.y * mv_speed;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		if (g->map.tiles[(int)(next_y)][(int)g->player.pos.x] == '0')
			g->player.pos.x -= g->player.dir.x * mv_speed;
		if (g->map.tiles[(int)(g->player.pos.y)][(int)(next_x)] == '0')
			g->player.pos.y -= g->player.dir.y * mv_speed;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		if (g->map.tiles[(int)(g->player.pos.y - g->ray.plane.y * mv_speed)][(int)g->player.pos.x] == '0'
			&& g->map.tiles[(int)(g->player.pos.y)][(int)(g->player.pos.x - g->ray.plane.x * mv_speed)] == '0')
				g->player.pos.y += mv_speed;
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		if (g->map.tiles[(int)(g->player.pos.y - g->ray.plane.y * mv_speed)][(int)g->player.pos.x] == '0'
			&& g->map.tiles[(int)(g->player.pos.y)][(int)(g->player.pos.x - g->ray.plane.x * mv_speed)] == '0')
				g->player.pos.y -= mv_speed;

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
/*=======
		mlx_close_window(game->mlx);
		ft_error("Game closed with esc.\n", 0, game); 	
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	// 	game->img->instances->y -= MV_SPEED;
	// if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	// 	game->img->instances->y += MV_SPEED;
	// if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	// 	game->img->instances->x -= MV_SPEED;
	// if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	// 	game->img->instances->x += MV_SPEED;
	// start nsloniow 200225 arrows will be used for camera! So just for now.
		// printf("%s %d img.y %u img.x %u\n", __FILE__, __LINE__, game->img->instances->y,game->img->instances->x);
		// printf("%s %d img.y %u img.x %u\n", __FILE__, __LINE__, game->miniplayer->instances->y,game->miniplayer->instances->x);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		game->img->instances->y -= MV_SPEED;
		printf("%s %d img.y %u img.x %u\n", __FILE__, __LINE__, game->img->instances->y,game->img->instances->x);
		game->miniplayer->instances->y -= MV_SPEED_MINI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		game->img->instances->y += MV_SPEED;
		game->miniplayer->instances->y += MV_SPEED_MINI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A) || mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->img->instances->x -= MV_SPEED;
		game->miniplayer->instances->x -= MV_SPEED_MINI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D) || mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->img->instances->x += MV_SPEED;
		game->miniplayer->instances->x += MV_SPEED_MINI;
	}
	// end nsloniow 200225
//>>>>>>> nsloniow_pullFynn
*/
}
