/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:57 by fforster          #+#    #+#             */
/*   Updated: 2025/05/13 15:45:46 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	set_speeds(mlx_t *mlx, double *mv_speed, double *rt_speed);
void		movement_keyhook(t_game *g);
void		hands_keyhook(t_game *g);
void		minimap_keyhook(t_game *g);
void		my_keyhook(mlx_key_data_t keydata, void *param);

// movement is much smoother when putting these keys in to the main loop
static void	set_speeds(mlx_t *mlx, double *mv_speed, double *rt_speed)
{
	*mv_speed = mlx->delta_time * MV_SPEED;
	*rt_speed = mlx->delta_time * RT_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
	{
		*mv_speed *= 2;
		*rt_speed *= 1.5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SUPER))
	{
		*mv_speed /= 2;
		*rt_speed /= 1.5;
	}
}

void	movement_keyhook(t_game *g)
{
	double	mv_speed;
	double	rt_speed;

	set_speeds(g->mlx, &mv_speed, &rt_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_W) || mlx_is_key_down(g->mlx, 265))
		walk_forward(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_S) || mlx_is_key_down(g->mlx, 264))
		walk_backwards(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		strafe_left(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		strafe_right(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		rotate_player(&g->player.dir, &g->ray.plane, rt_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		rotate_player(&g->player.dir, &g->ray.plane, -rt_speed);
}

void	hands_keyhook(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_SPACE)
		|| mlx_is_mouse_down(g->mlx, MLX_MOUSE_BUTTON_LEFT))
		g->player.punch = true;
	if (mlx_is_key_down(g->mlx, MLX_KEY_B)
		|| mlx_is_mouse_down(g->mlx, MLX_MOUSE_BUTTON_RIGHT))
		g->player.build = true;
	else
		g->player.build = false;
	if (g->player.punch)
		punch(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_W) || mlx_is_key_down(g->mlx, 265)
		|| mlx_is_key_down(g->mlx, MLX_KEY_S) || mlx_is_key_down(g->mlx, 264)
		|| mlx_is_key_down(g->mlx, MLX_KEY_A) || mlx_is_key_down(g->mlx, 68))
		g->player.moving = true;
	else
		g->player.moving = false;
	build_wall(g);
	sway_hands(g);
}

void	minimap_keyhook(t_game *g)
{
	if (g->show_minimap)
	{
		if (!g->minimap_drawn)
		{
			g->minimap->enabled = true;
			g->minifov->enabled = true;
			g->minimap_drawn = true;
		}
		if (g->changed_map)
		{
			minimap_change(g);
			g->changed_map = false;
		}
		draw_mini_fov(g);
	}
	else
	{
		if (g->minimap_drawn)
		{
			g->minimap->enabled = false;
			g->minifov->enabled = false;
			g->minimap_drawn = false;
		}
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game			*g;

	g = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(g->mlx);
		ft_error("Game closed with esc.\n", 0, g);
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		g->show_minimap = !g->show_minimap;
	if (keydata.key == MLX_KEY_BACKSPACE)
	{
		g->player.pos.y = g->map.spawn.y;
		g->player.pos.x = g->map.spawn.x;
	}
	if (g->ray.hit_x_wall && mlx_is_key_down(g->mlx, MLX_KEY_TAB))
	{
		print_ray_status(g);
		printf(ANSI_RED"xhitintersection = %f\n"ANSI_RESET, g->ray.x_intersect);
	}
	else if (mlx_is_key_down(g->mlx, MLX_KEY_TAB))
	{
		print_ray_status(g);
		printf(ANSI_GREEN"xintersection = %f\n"ANSI_RESET, g->ray.x_intersect);
	}
}
