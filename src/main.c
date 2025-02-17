/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:44 by fforster          #+#    #+#             */
/*   Updated: 2025/02/17 14:53:29 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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

	// Set every pixel of img to white
	ft_memset(game.bg->pixels, 255, game.bg->width * game.bg->height * sizeof(int32_t));
	ft_memset(game.img->pixels, get_rgba(200, 200, 200, 120), game.img->width * game.img->height * sizeof(int32_t));

	if (mlx_image_to_window(game.mlx, game.bg, 0, 0) < 0)
		ft_error("Image didn't arrive at window", 1, &game);
	if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
		ft_error("Image didn't arrive at window", 1, &game);
	printf("bg z = %d\n", game.bg->instances->z);
	printf("img z = %d\n", game.img->instances->z);

	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(EXIT_SUCCESS);
}
