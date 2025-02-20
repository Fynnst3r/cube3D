/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:44 by fforster          #+#    #+#             */
/*   Updated: 2025/02/20 13:40:12 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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
		free(tmp);
		tmp = NULL;
		free(buff);
		buff = NULL;
	}
	res = ft_split(map_lines, '\n');
	free(map_lines);
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
	// printf("map y = %zu/map x = %zu\n", map->max_y, map->max_x);
}

// this is just for testing mlx42 and draws a basic map with the wall texture using image_to_window
// y- and xsteps are the units and it steps to the next point where it should draw the tile
void	draw_texture_map(t_game game)
{
	int		xsteps;
	int		ysteps;
	size_t	y;
	size_t	x;

	xsteps = 100;
	ysteps = 100;
	y = 0;
	x = 0;
	while (game.map.tiles[y] != NULL)
	{
		while (game.map.tiles[y][x] != 0)
		{
			if (game.map.tiles[y][x] == '1')
				if (mlx_image_to_window(game.mlx, game.wall,
						x * xsteps, y * ysteps) < 0)
					ft_error("Error\nImage didn't arrive at window", 1, &game);
			x += 1;
		}
		x = 0;
		y += 1;
	}
}

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	(void)av;
	init_garbage_collector();
	ft_bzero(&game, sizeof(t_game));
	game.map.tiles = read_tiles("maps/test.cub");
	if (!game.map.tiles)
		ft_error("Error\nNo map", 2, &game);
	map_len(&game.map);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game.mlx = mlx_init(1600, 900, "cub3D", true);
	if (!game.mlx)
		ft_error("Error\nMLX has failed to initialze\n", 42, &game);

	game.bg = mlx_new_image(game.mlx, 1600, 900);
	if (!game.bg)
		ft_error("Error\nImage didn't create", 1, &game);
	game.img = mlx_new_image(game.mlx, 10, 10);
	if (!game.img)
		ft_error("Error\nImage didn't create", 1, &game);
	game.walltex = mlx_load_png("./textures/wallcub.png");

	// start 180225 set all pixels of a tile to one rgba colour
	// if (!game.img)
	// 	ft_error("Image didn't create", 1, &game);
	// int r = 255;
	// int g = 125;
	// int b = 0;
	// int a = 255;
	// // we set background to cyan and opac = not transparent.
	// // get_rgba is wizardry calculation using bitshifting
	// // int is 32 bits and each channal max 155, which is 8 bit and so all 
	// // bitshiftet to left by 24, 16, 8 and none we get rgba in a row as an int.
	// ft_pixset(game.bg, get_rgba(126, 220, 238, 255));
	// ft_pixset(game.img, get_rgba(r , g, b, a));
	// if (mlx_image_to_window(game.mlx, game.bg, 0, 0) < 0)
	// 	ft_error("Image didn't arrive at window", 1, &game);
	// if (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0)
	// 	ft_error("Image didn't arrive at window", 1, &game);
	//end 180225 

	if (!game.walltex)
		ft_error("Error\nCould not create wall image\n", 42, &game);
	game.wall = mlx_texture_to_image(game.mlx, game.walltex);

	// game.wall = mlx_new_image(game.mlx, 100, 100);
	// if (!game.wall)
	// 	ft_error("Image didn't create", 1, &game);

	// Set every pixel of img to white
	ft_memset(game.bg->pixels, 255, game.bg->width * game.bg->height * sizeof(int32_t));
	ft_memset(game.img->pixels, get_rgba(200, 200, 200, 150), game.img->width * game.img->height * sizeof(int32_t));
	// ft_memset(game.wall->pixels, get_rgba(200, 200, 200, 100), game.wall->width * game.wall->height * sizeof(int32_t));

	if (mlx_image_to_window(game.mlx, game.bg, 0, 0) < 0)
		ft_error("Error\nImage didn't arrive at window", 1, &game);
	if (mlx_image_to_window(game.mlx, game.img, 100, 100) < 0)
		ft_error("Error\nImage didn't arrive at window", 1, &game);
	// mlx_resize_image(game.wall, 100, 100);
	draw_texture_map(game);

	mlx_key_hook(game.mlx, my_keyhook, &game);
	// printf("%s %d\n", __FILE__, __LINE__);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	delete_trash();
	ft_bzero(get_workers(), sizeof(t_trashman));
	exit(EXIT_SUCCESS);
}
