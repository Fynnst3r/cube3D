/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:55:02 by fforster          #+#    #+#             */
/*   Updated: 2025/04/15 15:08:08 by fforster         ###   ########.fr       */
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

	factor = 3;
	// printf("factor %lf\n", factor);
	// factor = 4;
	mlx_resize_image(g->hands[0], g->hands[0]->width * factor, g->hands[0]->height * factor);
	if (mlx_image_to_window(g->mlx, g->hands[0], g->mlx->width - g->hands[0]->width, g->mlx->height - g->hands[0]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 8, g);
	mlx_resize_image(g->hands[1], g->hands[1]->width * factor, g->hands[1]->height * factor);
	if (mlx_image_to_window(g->mlx, g->hands[1], 0, g->mlx->height - g->hands[1]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 9, g);
	mlx_resize_image(g->hands[2], g->hands[2]->width * factor, g->hands[2]->height * factor);
	if (mlx_image_to_window(g->mlx, g->hands[2], 0, g->mlx->height - g->hands[2]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 10, g);
	mlx_resize_image(g->hands[3], g->hands[3]->width * factor, g->hands[3]->height * factor);
	if (mlx_image_to_window(g->mlx, g->hands[3], 0, g->mlx->height - g->hands[3]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 11, g);
	// g->hands[1]->enabled = false;
	g->hands[2]->enabled = false;
	g->hands[3]->enabled = false;
}

void	punch(t_game *g)
{
	double static	start_time = 0.0;
	static bool		animation_end = true;

	if (animation_end)
		start_time = mlx_get_time();
	animation_end = false;
	g->hands[1]->enabled = false; // extend arm
	g->hands[2]->enabled = true;
	if (start_time + 0.1 < mlx_get_time())
	{
		g->hands[2]->enabled = false; // full punch
		g->hands[3]->enabled = true;
	}
	if (start_time + 0.3 < mlx_get_time())
	{
		g->hands[3]->enabled = false; //retreat punch
		g->hands[2]->enabled = true;
	}
	if (start_time + 0.35 < mlx_get_time())
	{
		g->hands[2]->enabled = false; //end
		g->hands[1]->enabled = true;
		animation_end = true;
		g->punch = false;
	}
}
