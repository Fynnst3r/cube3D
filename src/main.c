/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:44 by fforster          #+#    #+#             */
/*   Updated: 2025/05/13 16:34:15 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	setup_game_state(t_game *game, int ac, char **av);
static void	setup_mlx_hooks(t_game *game);
int			main(int ac, char **av);

static void	setup_game_state(t_game *game, int ac, char **av)
{
	parse_scene(game, ac, av);
	parse_map(&game->map, &game->player, &game->textures, av[1]);
	game->mlx = mlx_init(S_WIDTH, S_HEIGHT, "cub3D", true);
	if (!game->mlx)
		ft_error("Error\nMLX has failed to initialze\n", 42, game);
	game->bg = mlx_new_image(game->mlx, S_WIDTH, S_HEIGHT);
	if (!game->bg)
		ft_error("Error\nImage didn't create", 1, game);
	ft_memset(game->bg->pixels, 255,
		game->bg->width * game->bg->height * sizeof(int32_t));
	if (mlx_image_to_window(game->mlx, game->bg, 0, 0) < 0)
		ft_error("Error\nImage didn't arrive at window", 1, game);
	init_raycaster(game);
	init_hands(game);
	init_minimap(game);
}

static void	setup_mlx_hooks(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_key_hook(game->mlx, my_keyhook, game);
	game->steal_mouse = true;
	mlx_set_mouse_pos(game->mlx,
		game->mlx->width / 2, game->mlx->height / 2);
	mlx_cursor_hook(game->mlx, my_cursor, game);
	mlx_mouse_hook(game->mlx, my_mouse_button, game);
	mlx_key_hook(game->mlx, my_keyhook, game);
	mlx_loop_hook(game->mlx, &raycaster_loop, game);
}

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	(void)av;
	init_garbage_collector();
	ft_bzero(&game, sizeof(t_game));
	setup_game_state(&game, ac, av);
	setup_mlx_hooks(&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(EXIT_SUCCESS);
}
