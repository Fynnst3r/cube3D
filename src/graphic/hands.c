/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:55:02 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 14:55:44 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_hands(t_game *g)
{
	double	factor;

	g->textures.hands[0] = mlx_load_png("./hands/right_hand.png");
	if (!g->textures.hands[0])
		ft_error("Texture ./hands/right_hand.png failed to load!", 1, g);
	g->hands[0] = mlx_texture_to_image(g->mlx, g->textures.hands[0]);
	if (!g->hands[0])
		ft_error("Error\nImage didn't create", 2, g);

	g->textures.hands[1] = mlx_load_png("./hands/lefthand_1blume.png");
	if (!g->textures.hands[1])
		ft_error("Texture ./hands/lefthand_1blume.png failed to load!", 1, g);
	g->hands[1] = mlx_texture_to_image(g->mlx, g->textures.hands[1]);
	if (!g->hands[1])
		ft_error("Error\nImage didn't create", 3, g);

	g->textures.hands[2] = mlx_load_png("./hands/lefthand_2blume.png");
	if (!g->textures.hands[2])
		ft_error("Texture ./hands/lefthand_2blume.png failed to load!", 4, g);
	g->hands[2] = mlx_texture_to_image(g->mlx, g->textures.hands[2]);
	if (!g->hands[2])
		ft_error("Error\nImage didn't create", 5, g);

	g->textures.hands[3] = mlx_load_png("./hands/lefthand_3blume.png");
	if (!g->textures.hands[3])
		ft_error("Texture ./hands/lefthand_3blume.png failed to load!", 6, g);
	g->hands[3] = mlx_texture_to_image(g->mlx, g->textures.hands[3]);
	if (!g->hands[3])
		ft_error("Error\nImage didn't create", 7, g);

	// height_ref_res = 720;
	// width_ref_res = 1280;
	factor = 2;
	// printf("factor_h %lf factor_w %lf\n", factor_h, factor_w);
	// factor = 1;
	// int x1 = (S_WIDTH -(4 * g->hands[0]->width))/2;
	// int x1 = (g->mlx->width -(4 * g->hands[0]->width * factor))/2;
	// int x1 = (g->mlx->width -(3 * ((g->hands[0]->width + g->hands[1]->width)/2) * factor))/2;
	// int x1 = (g->mlx->width -(3 * ((g->hands[0]->width + g->hands[1]->width)/2)* factor))/2;
	int x1 = (S_WIDTH -(3 * ((g->hands[0]->width + g->hands[1]->width)/2)* factor))/2;
	// int x1 = S_WIDTH -((6 * g->hands[0]->width * factor)/2);
	// int x1 = (S_WIDTH -((6 * g->hands[0]->width * factor)/2)) * factor;
	// int x1 = (S_WIDTH -((6 * g->hands[0]->width )/2)) * factor;
	// printf("swidth %d right hand 0 width %d x1 %d\n", S_WIDTH,g->hands[0]->width,x1);
	// printf("swidth %d left hand 0 width %d x1 %d\n", g->mlx->width,g->hands[1]->width,x1);
	// x1 = 300;
	// int x2 = S_WIDTH -x1 - g->hands[0]->width;
	// int x2 = g->mlx->width -x1 - g->hands[0]->width * factor;
	int x2 = S_WIDTH -x1 - g->hands[0]->width * factor;
	// printf("swidth %d right hand 0 width %d x2 %d\n", g->mlx->width,g->hands[0]->width,x2);
	mlx_resize_image(g->hands[0], g->hands[0]->width * factor, g->hands[0]->height * factor);
	// if (mlx_image_to_window(g->mlx, g->hands[0], g->mlx->width - g->hands[0]->width, g->mlx->height - g->hands[0]->height) < 0)
	if (mlx_image_to_window(g->mlx, g->hands[0], x2, g->mlx->height - g->hands[0]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 8, g);
	mlx_resize_image(g->hands[1], g->hands[1]->width * factor, g->hands[1]->height * factor);
	// if (mlx_image_to_window(g->mlx, g->hands[1], 0, g->mlx->height - g->hands[1]->height) < 0)
	if (mlx_image_to_window(g->mlx, g->hands[1], x1, g->mlx->height - g->hands[1]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 9, g);
	mlx_resize_image(g->hands[2], g->hands[2]->width * factor, g->hands[2]->height * factor);
	if (mlx_image_to_window(g->mlx, g->hands[2], x1, g->mlx->height - g->hands[2]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 10, g);
	mlx_resize_image(g->hands[3], g->hands[3]->width * factor, g->hands[3]->height * factor);
	if (mlx_image_to_window(g->mlx, g->hands[3], x1, g->mlx->height - g->hands[3]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 11, g);

	g->textures.wallcrack = mlx_load_png("./textures/wallcrack.png");
	if (!g->textures.wallcrack)
		ft_error("Texture ./textures/wallcrack.png failed to load!", 1, g);
	g->wallcrack = mlx_texture_to_image(g->mlx, g->textures.wallcrack);
	if (!g->wallcrack)
		ft_error("Error\nImage didn't create", 2, g);

	g->hands[2]->enabled = false;
	g->hands[3]->enabled = false;
	g->hands[0]->instances->y += 15;
	g->hands[1]->instances->y += 15;
}

bool	change_map_element(t_game *g, char src, char dest)
{
	char	**m;

	m = g->map.tiles;
	if (g->player.look_x_wall)
	{
		if (m[(size_t)g->player.pos.y][(size_t)g->player.pos.x + 1] == src
			&& g->player.dir.x > 0)
			m[(size_t)g->player.pos.y][(size_t)g->player.pos.x + 1] = dest;
		else if (m[(size_t)g->player.pos.y][(size_t)g->player.pos.x - 1] == src
				&& g->player.dir.x < 0)
			m[(size_t)g->player.pos.y][(size_t)g->player.pos.x - 1] = dest;
		else
			return (false);
	}
	else
	{
		if (m[(size_t)g->player.pos.y + 1][(size_t)g->player.pos.x] == src
			&& g->player.dir.y > 0)
			m[(size_t)g->player.pos.y + 1][(size_t)g->player.pos.x] = dest;
		else if (m[(size_t)g->player.pos.y - 1][(size_t)g->player.pos.x] == src
			&& g->player.dir.y < 0)
			m[(size_t)g->player.pos.y - 1][(size_t)g->player.pos.x] = dest;
		else
			return (false);
	}
	g->changed_map = true;
	return (true);
}

static void	hit_wall(t_game *g)
{
	g->hands[2]->enabled = false;
	g->hands[1]->enabled = true;
	if (!change_map_element(g, '1', '2'))
		if (!change_map_element(g, 'D', 'd'))
			if (!change_map_element(g, 'd', '0'))
				;
	g->player.punch = false;
}

void	punch(t_game *g)
{
	double static	start_time = 0.0;
	static bool		animation_end = true;

	if (animation_end)
		start_time = mlx_get_time();
	animation_end = false;
	g->hands[1]->enabled = false;
	g->hands[2]->enabled = true;
	if (start_time + 0.1 < mlx_get_time())
	{
		g->hands[2]->enabled = false;
		g->hands[3]->enabled = true;
	}
	if (start_time + 0.33 < mlx_get_time())
	{
		g->hands[3]->enabled = false;
		g->hands[2]->enabled = true;
	}
	if (start_time + 0.38 < mlx_get_time())
	{
		hit_wall(g);
		animation_end = true;
	}
}

void	sway_hands(t_game *g)
{
	static int		direction_x = 1;
	static int		direction_y = -1;
	int				max_x;
	int				min_x;
	int				max_y;
	int				min_y;
	int				factor;
	int x1;
	
	x1 = (S_WIDTH -(3 * ((g->hands[0]->width + g->hands[1]->width)/2)* 1))/2;
	if (!g->player.moving)
	{
		// printf("mlx width %d height %d\n", g->mlx->width, g->mlx->height);
		// g->hands[0]->instances->x = S_WIDTH - g->hands[0]->width;
		// g->hands[1]->instances->x = 0;
		// x1 = (g->mlx->width -(3 * ((g->hands[0]->width + g->hands[1]->width)/2)* 1))/2;
		// x2 = g->mlx->width -x1 - g->hands[0]->width * 1;

		g->hands[0]->instances->x = S_WIDTH -x1 - g->hands[0]->width * 1;
		g->hands[1]->instances->x = x1; 
		g->hands[0]->instances->y = S_HEIGHT - g->hands[0]->height + 15;
		g->hands[1]->instances->y = S_HEIGHT - g->hands[1]->height + 15;
		return ;
	}
	max_x = x1 + 22;
	min_x = x1 - 22;
	max_y = g->mlx->height - g->hands[0]->height + 11 + 15;
	min_y = max_y - 22;
	// printf("max_x %d left hand inst x %d \n", max_x, g->hands[1]->instances->x);
	if (g->hands[1]->instances->x > max_x || min_x > g->hands[1]->instances->x)
		direction_x *= -1;
	if (g->hands[0]->instances->y > max_y || min_y > g->hands[0]->instances->y)
		direction_y *= -1;
	factor = 1.5;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT))
		factor += 0.5;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SUPER))
		factor -= 0.5;
	g->hands[0]->instances->x += direction_x * factor;
	g->hands[1]->instances->x += direction_x * factor;
	g->hands[0]->instances->y += direction_y * factor;
	g->hands[1]->instances->y += direction_y * factor;
}
