/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:44 by fforster          #+#    #+#             */
/*   Updated: 2025/02/18 15:40:21 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
		// return (a << 24 | r << 16 | g << 8 | b);
}

void	ft_pixset(mlx_image_t *img, int colour)
{
	u_int32_t x = 0;
	u_int32_t y = 0;
	while (y < img->height)
	{
		while (x++ < img->width)
			mlx_put_pixel(img, x, y, colour);
		x = 0;
		y++;
	}
}

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	(void)av;
	init_garbage_collector();
	ft_bzero(&game, sizeof(t_game));
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game.mlx = mlx_init(1600, 900, "cub3D", true);
	if (!game.mlx)
		ft_error("Error\nMLX has failed to initialze\n", 42, &game);

	game.bg = mlx_new_image(game.mlx, 1600, 900);
	if (!game.bg)
		ft_error("Image didn't create", 1, &game);

	game.img = mlx_new_image(game.mlx, 100, 100);
	if (!game.img)
		ft_error("Image didn't create", 1, &game);
	int r = 255;
	int g = 125;
	int b = 0;
	int a = 255;
	// we set background to cyan and opac = not transparent.
	// get_rgba is wizardry calculation using bitshifting
	// int is 32 bits and each channal max 155, which is 8 bit and so all 
	// bitshiftet to left by 24, 16, 8 and none we get rgba in a row as an int.
	ft_pixset(game.bg, get_rgba(126, 220, 238, 255));
	ft_pixset(game.img, get_rgba(r , g, b, a));
	if (mlx_image_to_window(game.mlx, game.bg, 0, 0) < 0)
		ft_error("Image didn't arrive at window", 1, &game);
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
		ft_error("Image didn't arrive at window", 1, &game);

	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(EXIT_SUCCESS);
}
