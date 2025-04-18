/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:16:57 by fforster          #+#    #+#             */
/*   Updated: 2025/04/18 16:17:36 by nsloniow         ###   ########.fr       */
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

// movement is much smoother when putting these keys in to the main loop
void	movement_keyhook(t_game *g)
{
	double	rt_speed;
	double	mv_speed;

	rt_speed = g->mlx->delta_time * RT_SPEED;
	mv_speed = g->mlx->delta_time * MV_SPEED;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT))
	{
		mv_speed *= 2;
		rt_speed *= 1.5;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SUPER))
	{
		mv_speed /= 2;
		rt_speed /= 1.5;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_W) || mlx_is_key_down(g->mlx, 265))
	{
		walk_forward(g->map.tiles, &g->player.pos, &g->player.dir, mv_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S) || mlx_is_key_down(g->mlx, 264))
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
		rotate_player(&g->player.dir, &g->ray.plane, rt_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
	{
		rotate_player(&g->player.dir, &g->ray.plane, -rt_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_SPACE)
		|| mlx_is_mouse_down(g->mlx, MLX_MOUSE_BUTTON_LEFT))
		g->player.punch = true;
	if (mlx_is_key_down(g->mlx, MLX_KEY_B)
		|| mlx_is_mouse_down(g->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		change_map_element(g, '0', 'D');
	}
	if (g->player.punch)
		punch(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_W) || mlx_is_key_down(g->mlx, 265) || mlx_is_key_down(g->mlx, MLX_KEY_S) || mlx_is_key_down(g->mlx, 264) || mlx_is_key_down(g->mlx, MLX_KEY_A) || mlx_is_key_down(g->mlx, MLX_KEY_D))
		g->player.moving = true;
	else
		g->player.moving = false;
	sway_hands(g);
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
	{
		g->show_minimap = !g->show_minimap;
		if (EASTER)
			g->mini_img = !g->mini_img;
	}
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

// g->hands[1]->enabled = false; // extend arm
// g->hands[2]->enabled = true;
// if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_REPEAT)
// {
// 	g->hands[2]->enabled = false; // full punch
// 	g->hands[3]->enabled = true;
// }
// if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_REPEAT)
// {
// 	g->hands[3]->enabled = false; //retreat punch
// 	g->hands[2]->enabled = true;
// }
// if (button != MLX_MOUSE_BUTTON_LEFT)
// {
// 	g->hands[2]->enabled = false; //end
// 	g->hands[1]->enabled = true;
// }
void	my_mouse_button(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	(void)button;
	(void)action;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_PRESS)
	{
		g->steal_mouse = !g->steal_mouse;
		mlx_set_cursor_mode(g->mlx, MLX_MOUSE_NORMAL);
	}

	// if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	// if (mlx_is_mouse_down(g->mlx, MLX_MOUSE_BUTTON_LEFT))
	// {
	// 	g->punch = true;
	// }
}

void	my_cursor(double xpos, double ypos, void *param)
{
	t_game	*g;
	double	rt_speed;

	g = (t_game *)param;
	(void)ypos;
	if (!g->steal_mouse)
		return ;
	mlx_set_cursor_mode(g->mlx, MLX_MOUSE_HIDDEN);
	rt_speed = g->mlx->delta_time * RT_SPEED;
	// printf("xpos = %lf\nypos = %lf\n", xpos, ypos);
	// printf("xpos  - g->mlx->width / 2 = %lf\n", xpos - g->mlx->width / 2);
	if (xpos > g->mlx->width / 2 + 0.3)
	{
		rotate_player(&g->player.dir, &g->ray.plane, rt_speed * (xpos - g->mlx->width / 2) * M_PI_4 / 4);
	}
	if (g->mlx->width / 2 - 0.3 > xpos)
	{
		rotate_player(&g->player.dir, &g->ray.plane, -rt_speed * (g->mlx->width / 2 - xpos) * M_PI_4 / 4);
	}
	mlx_set_mouse_pos(g->mlx, g->mlx->width / 2, g->mlx->height / 2);
}
