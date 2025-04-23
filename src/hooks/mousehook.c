/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousehook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:21:51 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 19:22:33 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
