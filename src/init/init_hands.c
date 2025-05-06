/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:18:09 by fforster          #+#    #+#             */
/*   Updated: 2025/04/24 15:04:14 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	load_hands(t_game *g)
{
	int		i;
	char	*paths[8];

	paths[0] = "./hands/right_hand.png";
	paths[1] = "./hands/lefthand_1blume.png";
	paths[2] = "./hands/lefthand_2blume.png";
	paths[3] = "./hands/lefthand_3blume.png";
	paths[4] = "./hands/right_hand_leastlight.png";
	paths[5] = "./hands/right_hand_midlight.png";
	paths[6] = "./hands/right_hand_fulllight.png";
	paths[7] = NULL;
	i = 0;
	while (i < 7)
	{
		g->textures.hands[i] = mlx_load_png(paths[i]);
		if (!g->textures.hands[i])
			ft_error("Hand texture failed to load!", i, g);
		g->hands[i] = mlx_texture_to_image(g->mlx, g->textures.hands[i]);
		if (!g->hands[i])
			ft_error("Error\nHand Image didn't create", i, g);
		i++;
	}
}

static void	resize_hands(mlx_image_t *hands[4])
{
	double	referenz_w;
	double	referenz_h;

	referenz_w = (double)S_WIDTH / 1920;
	referenz_h = (double)S_HEIGHT / 1080;
	mlx_resize_image(hands[0], hands[0]->width * 3 * referenz_w,
		hands[0]->height * 3 * referenz_h);
	mlx_resize_image(hands[1], hands[1]->width * 3 * referenz_w,
		hands[1]->height * 3 * referenz_h);
	mlx_resize_image(hands[2], hands[2]->width * 3 * referenz_w,
		hands[2]->height * 3 * referenz_h);
	mlx_resize_image(hands[3], hands[3]->width * 3 * referenz_w,
		hands[3]->height * 3 * referenz_h);
	mlx_resize_image(hands[4], hands[4]->width * 3 * referenz_w,
		hands[4]->height * 3 * referenz_h);
	mlx_resize_image(hands[5], hands[5]->width * 3 * referenz_w,
		hands[5]->height * 3 * referenz_h);
	mlx_resize_image(hands[6], hands[6]->width * 3 * referenz_w,
		hands[6]->height * 3 * referenz_h);
}

static void	place_hands(t_game *g)
{
	int		x1;
	int		x2;
	int		i;

	x1 = (S_WIDTH -((g->hands[0]->width + g->hands[1]->width))) / 2;
	x2 = S_WIDTH - x1 - g->hands[0]->width * 2;
	if (mlx_image_to_window(g->mlx, g->hands[4],
			x2, g->mlx->height - g->hands[4]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 8, g);
	if (mlx_image_to_window(g->mlx, g->hands[5],
			x2, g->mlx->height - g->hands[5]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 8, g);
	if (mlx_image_to_window(g->mlx, g->hands[6],
			x2, g->mlx->height - g->hands[6]->height) < 0)
		ft_error("Error\nImage didn't arrive at window", 8, g);
	i = -1;
	while (++i < 4)
	{
		if (mlx_image_to_window(g->mlx, g->hands[i], 0, 0) < 0)
			ft_error("Error\nImage didn't arrive at window", 9, g);
	}
	g->hands[2]->enabled = false;
	g->hands[3]->enabled = false;
	g->hands[0]->instances->y += 15;
	g->hands[1]->instances->y += 15;
}

void	init_hands(t_game *g)
{
	load_hands(g);
	resize_hands(g->hands);
	place_hands(g);
	if (!g->textures.wallcrack)
	{
		printf("xd\n");
		g->textures.wallcrack = mlx_load_png("./textures/wallcrack.png");
		if (!g->textures.wallcrack)
			ft_error("Texture ./textures/wallcrack.png failed to load!", 12, g);
	}
	g->wallcrack = mlx_texture_to_image(g->mlx, g->textures.wallcrack);
	if (!g->wallcrack)
		ft_error("Error\nImage didn't create", 13, g);
}
