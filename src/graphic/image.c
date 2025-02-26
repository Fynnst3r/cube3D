/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/02/21 13:33:44 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	draw_mini_map(t_game game);
int		get_rgba(int r, int g, int b, int a);
void	pixset(mlx_image_t *img, int colour);
void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords xy,
			t_height_width height_width);

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	pixset(mlx_image_t *img, int colour)
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

void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords xy,
	t_height_width height_width)
{
	// u_int32_t x = 0;
	// u_int32_t y = 0;
	u_int32_t x = xy.x;
	u_int32_t y = xy.y;
	printf("%s %d - width %u height %u\n", __FILE__, __LINE__, height_width.width, height_width.height) ;
	while (y < height_width.height)
	{
		while (x++ < height_width.width)
		{
			// printf("%s %d xy.y %f xy.x %f\n", __FILE__, __LINE__, xy.y, xy.x) ;
			// printf("%s %d y %f x %f\n", __FILE__, __LINE__, y, x) ;
			// mlx_put_pixel(img, xy.x, xy.y, colour);
			mlx_put_pixel(img, x, y, colour);
		}
		x = 0;
		y++;
	}
}

// void	draw_texture_map(t_game game)
// {
// 	int		xsteps;
// 	int		ysteps;
// 	size_t	y;
// 	size_t	x;

// 	xsteps = 100;
// 	ysteps = 100;
// 	y = 0;
// 	x = 0;
// 	while (game.map.tiles[y] != NULL)
// 	{
// 		while (game.map.tiles[y][x] != 0)
// 		{
// 			if (game.map.tiles[y][x] == '1')
// 				if (mlx_image_to_window(game.mlx, game.wall,
// 						x * xsteps, y * ysteps) < 0)
// 					ft_error("Error\nImage didn't arrive at window", 1, &game);
// 			x += 1;
// 		}
// 		x = 0;
// 		y += 1;
// 	}
// }

// this draws the wall only
// void	draw_mini_map(t_game game)
// {
// 	int		xsteps;
// 	int		ysteps;
// 	size_t	y;
// 	size_t	x;

// 	xsteps = 10;
// 	ysteps = 10;
// 	y = 0;
// 	x = 0;
// 	// into init
// 	game.mini = mlx_new_image(game.mlx, 10, 19);
// 	//
// 	while (game.map.tiles[y] != NULL)
// 	{
// 		while (game.map.tiles[y][x] != 0)
// 		{
// 			if (game.map.tiles[y][x] == '1')
// 			{
// 				pixset(game.mini, get_rgba(126, 220, 238, 255));
// 				if (mlx_image_to_window(game.mlx, game.mini,
// 						x * xsteps, y * ysteps) < 0)
// 				{
// 					ft_error("Error\nImage didn't arrive at window", 1, &game);
// 				}
// 			}
// 			x += 1;
// 		}
// 		x = 0;
// 		y += 1;
// 	}
// }

void	draw_mini_map(t_game game)
{
	int		xsteps;
	int		ysteps;
	size_t	y;
	size_t	x;
	t_cords	yx;
	t_height_width	height_width;

	xsteps = 100;
	ysteps = 100;
	// xsteps = 1;
	// ysteps = 1;
	height_width.height = ysteps;
	height_width.width = xsteps;
	y = 0;
	x = 0;
	
	// into init
	// game.minimap = mlx_new_image(game.mlx, game.map.max_x * 10, game.map.max_y * 10);
	// printf("%s %d map max y %zu  map max x %zu\n", __FILE__, __LINE__, game.map.max_y, game.map.max_x);
	game.minimap = mlx_new_image(game.mlx, game.map.max_x * xsteps, game.map.max_y * ysteps);
	//
	while (game.map.tiles[y] != NULL)
	{
		while (game.map.tiles[y][x] != 0)
		{
			// if (game.map.tiles[y][x] == '1')
			// {
				yx.y = y * ysteps;
				yx.x = x * xsteps;
				printf("%s %d yx.y %f yx.x %f\n", __FILE__, __LINE__, yx.y, yx.x) ;
				pixset_yx_height_width(game.minimap, get_rgba(0, 77, 77, 255),
					yx, height_width);
				// ft_memset(game.minimap->pixels, get_rgba(0, 77, 77, 255), 
				// 	game.minimap->width * game.minimap->height * sizeof(int32_t));
				// mlx_image_to_window(game.mlx, game.minimap,x,y);
			// }
			x += 1;
			
		}
		x = 0;
		y += 1;
	}
				if (mlx_image_to_window(game.mlx, game.minimap,x,y) < 0)
						// x * xsteps, y * ysteps) < 0)

				{
					ft_error("Error\nImage didn't arrive at window", 1, &game);
				}
// mlx_resize_image()
}

