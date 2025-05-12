/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousehook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:21:51 by fforster          #+#    #+#             */
/*   Updated: 2025/05/12 09:49:01 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	my_mouse_button(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);
void	my_cursor(double xpos, double ypos, void *param);
void	print_ray_status(t_game *g);

void	my_mouse_button(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
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
		mlx_set_mouse_pos(g->mlx, g->mlx->width / 2, g->mlx->height / 2);
	}
}

// M_PI_4 <- this macro is only on apples version of the math library
// double	pi_4 = 0.785398163397448309615660845819875721;
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
	if (xpos > g->mlx->width / 2 + 0.3)
	{
		rotate_player(&g->player.dir,
			&g->ray.plane, rt_speed * (xpos - g->mlx->width / 2) * M_PI_4 / 4);
	}
	if (g->mlx->width / 2 - 0.3 > xpos)
	{
		rotate_player(&g->player.dir,
			&g->ray.plane, -rt_speed * (g->mlx->width / 2 - xpos) * M_PI_4 / 4);
	}
	mlx_set_mouse_pos(g->mlx, g->mlx->width / 2, g->mlx->height / 2);
}

//prints various info of the state of the ray for debug
// printf("\n\nmlx width %d height %d\nleft hand w %d h %d x %d y %d\n
// 	right hand w %d h %d x %d y %d\n", g->mlx->width, g->mlx->height,
// 	g->hands[1]->width, g->hands[1]->height, g->hands[1]->instances->x,
// 	g->hands[1]->instances->y, g->hands[0]->width, g->hands[0]->height,
// 	g->hands[0]->instances->x, g->hands[0]->instances->y);
void	print_ray_status(t_game *g)
{
	printf(ANSI_GREEN"PLAYER y %f - PLAYER x %f\n"ANSI_RESET, g->player.pos.y,
		g->player.pos.x);
	printf("PLAYERdir x %f - PLAYERdir y %f\n", g->player.dir.x,
		g->player.dir.y);
	printf("plane x %f - plane y %f\n", g->ray.plane.x, g->ray.plane.y);
	printf("camera x %f\n", g->ray.camera_x);
	printf(ANSI_BLUE"ray tile x %zu - y %zu\n"ANSI_RESET, g->ray.tile_x,
		g->ray.tile_y);
	printf("ray_dir x %f - ray_dir y %f\n", g->ray.ray_dir.x, g->ray.ray_dir.y);
	printf(ANSI_YELLOW"side_dist x %f - side_dist y %f\n"ANSI_RESET,
		g->ray.side_dist.x, g->ray.side_dist.y);
	printf(ANSI_MAGENTA"delta_dist x %f - delta_dist y %f\n"ANSI_RESET,
		g->ray.delta_dist.x, g->ray.delta_dist.y);
	printf("perpendicular_wall_dist %f\n", g->ray.perp_wall_dist);
	printf("go x %i, go y %i\n\n", g->ray.go_x, g->ray.go_y);
	printf("looking at x_wall %d\n", g->player.look_x_wall);
}
