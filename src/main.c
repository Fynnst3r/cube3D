/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:44 by fforster          #+#    #+#             */
/*   Updated: 2025/03/14 17:02:05 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// READS ENTIRE FILE no checks at all
// and it deletes all empty lines because of ft_split
char	**read_tiles(char *av)
{
	int		fd;
	char	*map_lines;
	char	*buff;
	char	*tmp;
	char	**res;

	map_lines = ft_strdup("");
	fd = open(av, O_RDONLY);
	while (1)
	{
		tmp = map_lines;
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		map_lines = f_strjoin(tmp, buff);
		ft_free(tmp);
		tmp = NULL;
		ft_free(buff);
		buff = NULL;
	}
	res = ft_split(map_lines, '\n');
	ft_free(map_lines);
	map_lines = NULL;
	close(fd);
	return (res);
}

// tiles needs to be seperated from other scene variables like NS or F and C
void	map_len(t_map *map)
{
	size_t	y;

	y = -1;
	while (map->tiles[++y])
		if (ft_strlen(map->tiles[y]) > map->max_y)
			map->max_x = ft_strlen(map->tiles[y]);
	map->max_y = y;
	printf("map y = %zu/map x = %zu\n", map->max_y, map->max_x);
}

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	(void)av;
	init_garbage_collector();
	ft_bzero(&game, sizeof(t_game));
	game.map.tiles = read_tiles("maps/simple.cub");
	if (!game.map.tiles)
		ft_error("Error\nNo map", 2, &game);
	map_len(&game.map);
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
	game.img = mlx_new_image(game.mlx, game.textures.walltex->width, game.textures.walltex->height);
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
	draw_mini_map(&game);
	mlx_resize_image(game.minimap, game.minimap->width * MINI_RESIZE_FACTOR,
		game.minimap->height * MINI_RESIZE_FACTOR);
	mlx_key_hook(game.mlx, my_keyhook, &game);
	mlx_loop_hook(game.mlx, &raycaster_loop, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(EXIT_SUCCESS);
}
