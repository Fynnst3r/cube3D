/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:44 by fforster          #+#    #+#             */
/*   Updated: 2025/04/08 19:12:09 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	(void)av;
	init_garbage_collector();
	ft_bzero(&game, sizeof(t_game));
	parse_scene(&game, ac, av);
	parse_map(&game.map, &game.player, &game.textures, av[1]);
	printf(ANSI_RED"AAAAAAAA\n"ANSI_RESET);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game.mlx = mlx_init(S_WIDTH, S_HEIGHT, "cub3D", true);
	if (!game.mlx)
		ft_error("Error\nMLX has failed to initialze\n", 42, &game);
	game.bg = mlx_new_image(game.mlx, S_WIDTH, S_HEIGHT);
	if (!game.bg)
		ft_error("Error\nImage didn't create", 1, &game);
	game.textures.walltex = mlx_load_png("./textures/test.png");
	if (!game.textures.walltex)
		ft_error("Error\nCould not create wall image\n", 42, &game);
	game.img = mlx_new_image(game.mlx, game.textures.no_tex->width, game.textures.no_tex->height);
	if (!game.img)
		ft_error("Error\nImage didn't create", 1, &game);
	// game.wall = mlx_texture_to_image(game.mlx, game.textures.walltex);
	// game.wall = mlx_new_image(game.mlx, 100, 100);
	// if (!game.wall)
	// 	ft_error("Image didn't create", 1, &game);

	// Set every pixel of img to white
	ft_memset(game.bg->pixels, 255, game.bg->width * game.bg->height * sizeof(int32_t));

	if (mlx_image_to_window(game.mlx, game.bg, 0, 0) < 0)
		ft_error("Error\nImage didn't arrive at window", 1, &game);
	// if (mlx_image_to_window(game.mlx, game.wall, 100, 100) < 0)
		// ft_error("Error\nImage didn't arrive at window", 1, &game);
	draw_half_tex(&game);
	mlx_resize_image(game.img, 100, 100);
	init_raycaster(&game);
	// draw_mini_map(&game);
	// mlx_resize_image(game.minimap, game.minimap->width * MINI_RESIZE_FACTOR,
	// 	game.minimap->height * MINI_RESIZE_FACTOR);
	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_loop_hook(game.mlx, &raycaster_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(EXIT_SUCCESS);
}
