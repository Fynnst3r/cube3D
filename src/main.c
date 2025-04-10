/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:44 by fforster          #+#    #+#             */
/*   Updated: 2025/04/10 15:59:34 by fforster         ###   ########.fr       */
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
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game.mlx = mlx_init(S_WIDTH, S_HEIGHT, "cub3D", true);
	if (!game.mlx)
		ft_error("Error\nMLX has failed to initialze\n", 42, &game);
	game.bg = mlx_new_image(game.mlx, S_WIDTH, S_HEIGHT);
	if (!game.bg)
		ft_error("Error\nImage didn't create", 1, &game);
		// game.textures[0].walltex = mlx_load_png("./textures/tx10x10px.png");
	// game.textures[0].walltex = mlx_load_png("./textures/test.png");
	// game.textures.walltex = mlx_load_png("./textures/wallcub.png");
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	// game.textures->walltex = mlx_load_png("./textures/wallcub.png");
	// game.textures[0].walltex = mlx_load_png("./textures/wallcub.png");
	// game.textures[0].walltex = mlx_load_png("./textures/wallcub2.png");
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	// if (!game.textures[0].walltex)
		// ft_error("Error\nCould not create wall image\n", 42, &game);
	// game.img = mlx_new_image(game.mlx, game.textures[0].walltex->width,
	// 							game.textures[0].walltex->height);
	// // game.img = mlx_new_image(game.mlx, game.textures[1].walltex->width, game.textures[1].walltex->height);
	// if (!game.img)
	// 	ft_error("Error\nImage didn't create", 1, &game);
	// game.textures[2].walltex = mlx_load_png("./textures/green_tx10x10px.png");
	// if (!game.textures[2].walltex)
		// ft_error("Error\nCould not creat/e wall image\n", 42, &game);
	// game.textures[3].walltex = mlx_load_png("./textures/blue_tx10x10px.png");
	// if (!game.textures[3].walltex)
		// ft_error("Error\nCould not create wall image\n", 42, &game);
	// game.textures[4].walltex = mlx_load_png("./textures/yellow_tx10x10px.png");
	// if (!game.textures[4].walltex)
		// ft_error("Error\nCould not create wall image\n", 42, &game);
	// game.textures[1].walltex = mlx_load_png("./textures/wallcub2.png");
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	// if (!game.textures[1].walltex)
		// ft_error("Error\nCould not create wall image\n", 42, &game);
	// game.img = mlx_new_image(game.mlx, game.textures.walltex->width, game.textures.walltex->height);
	// if (!game.img)
	// 	ft_error("Error\nImage didn't create", 1, &game);
	// // game.wall = mlx_texture_to_image(game.mlx, game.textures.walltex);
	// // game.wall = mlx_texture_to_image(game.mlx, game.textures[0].walltex);
	// game.wall = mlx_new_image(game.mlx, 100, 100);
	// // game.wall = mlx_texture_to_image(game.mlx, game.textures[0].walltex);
	// // game.wall = mlx_new_image(game.mlx, 1400, 980);
	// if (!game.wall)
	// 	ft_error("Image didn't create", 1, &game);

	// Set every pixel of img to white
	ft_memset(game.bg->pixels, 255, game.bg->width * game.bg->height
				* sizeof(int32_t));
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	if (mlx_image_to_window(game.mlx, game.bg, 0, 0) < 0)
		ft_error("Error\nImage didn't arrive at window", 1, &game);
	// if (mlx_image_to_window(game.mlx, game.wall, 100, 100) < 0)
		// ft_error("Error\nImage didn't arrive at window", 1, &game);
	// draw_half_tex(&game);
	// mlx_resize_image(game.img, 100, 100);
	init_raycaster(&game);
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	draw_mini_map(&game);
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	// draw_fov_direction_line(&game);
	draw_mini_fov(&game);
	// mlx_resize_image(game.minimap, game.minimap->width * MINI_RESIZE_FACTOR,
	// 	game.minimap->height * MINI_RESIZE_FACTOR);
	mlx_key_hook(game.mlx, my_keyhook, &game);
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	mlx_loop_hook(game.mlx, &raycaster_loop, &game);
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	mlx_loop(game.mlx);
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	mlx_terminate(game.mlx);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(EXIT_SUCCESS);
}
