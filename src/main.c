/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:44 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 15:23:16 by fforster         ###   ########.fr       */
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
	// Set every pixel of img to white
	ft_memset(game.bg->pixels, 255, game.bg->width * game.bg->height
				* sizeof(int32_t));
	if (mlx_image_to_window(game.mlx, game.bg, 0, 0) < 0)
		ft_error("Error\nImage didn't arrive at window", 1, &game);
	// game.img = mlx_new_image(game.mlx, game.textures.ea_tex->width, game.textures.ea_tex->height);
	// if (!game.img)
		// ft_error("Error\nImage didn't create", 1, &game);
	// draw_half_tex(&game);
	// mlx_resize_image(game.img, 500, 500);
	init_raycaster(&game);
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	// draw_mini_map(&game);
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	// draw_fov_direction_line(&game);
	draw_hands(&game);
	init_minimap(&game);
	// draw_mini_fov(&game);
	// mlx_resize_image(game.minimap, game.minimap->width * mini_resize_factor,
	// 	game.minimap->height * mini_resize_factor);
	mlx_key_hook(game.mlx, my_keyhook, &game);
	game.steal_mouse = true;
	mlx_set_mouse_pos(game.mlx, game.mlx->width / 2, game.mlx->height / 2);
	mlx_cursor_hook(game.mlx, my_cursor, &game);
	// printf("%s %d            \n\n", __FILE__, __LINE__);
	mlx_mouse_hook(game.mlx, my_mouse_button, &game);
	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_loop_hook(game.mlx, &raycaster_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(EXIT_SUCCESS);
}

// to do: 	scale minimap by map size AND maybe resolution size too
//			scale hands by resolution size
//			improve performance of wallcrack
//			make custom loadable wallcrack
//			add breakable walls (2 is crack only, 3 is breakable and 4 is both. so 1 is not breakable, but crackable to 2, 2 is cracked, 3 is not but can be cracked to 4 and also be placed, 0 is no wall)
//			1 D no crack
//			2 d with crack
//
//
//fix:		placing blocks is wierd, some times it places them behind or another one two infront of you
