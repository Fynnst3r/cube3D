/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/02/25 16:28:39 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	draw_mini_map(t_game game);
void	draw_mini_player(t_game *game);
int		get_rgba(int r, int g, int b, int a);
void	pixset(mlx_image_t *img, int colour);
void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
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
// #include "MLX42/MLX42_Int.h"
// # define BPP sizeof(int32_t) /* Only support RGBA */
void ft_mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void ft_mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	// MLX_NONNULL(image);
	// MLX_ASSERT(x < image->width, "Pixel is out of bounds");
	// MLX_ASSERT(y < image->height, "Pixel is out of bounds");
// printf("%s %d put px  y %u x %u\n", __FILE__, __LINE__, y, x) ;
	// uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];
	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
	// printf("%s %d put px  y %u x %u\n", __FILE__, __LINE__, y, x) ;
	ft_mlx_draw_pixel(pixelstart, color);
	// printf("%s %d put px  y %u x %u\n", __FILE__, __LINE__, y, x) ;
}

void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
	t_height_width height_width)
{
	u_int32_t x = 0;
	u_int32_t y = 0;
	// u_int32_t x = xy.x;
	// u_int32_t y = xy.y;
	printf("%s %d - width %u height %u colour %d\n", __FILE__, __LINE__, height_width.width, height_width.height, colour) ;
	// printf("%s %d y %u x %u\n", __FILE__, __LINE__, y, x) ;
	while (y < height_width.height)
	{
		// printf("%s %d y %u x %u\n", __FILE__, __LINE__, y, x) ;
		// printf("%s %d xy.y %u xy.x %u\n", __FILE__, __LINE__, xy.y, xy.x) ;
		// printf("%s %d xy.y + y %u xy.x + x %u\n", __FILE__, __LINE__, xy.y + y, xy.x + x) ;
		// printf("%s %d xy.y + y %d xy.x + x %d\n", __FILE__, __LINE__, xy.y + y, xy.x + x) ;
		while (x < height_width.width)
		{
			// printf("%s %d xy.y %f xy.x %f\n", __FILE__, __LINE__, xy.y, xy.x) ;
			// printf("%s %d xy.y %d xy.x %d\n", __FILE__, __LINE__, xy.y, xy.x) ;
			// printf("%s %d y %u x %u\n", __FILE__, __LINE__, y, x) ;
			// printf("%s %d xy.y + y %d xy.x + x %d\n", __FILE__, __LINE__, xy.y + y, xy.x + x) ;
			// mlx_put_pixel(img, xy.x, xy.y, colour);
			// ft_mlx_put_pixel(img, x + xy.x, y + xy.y, colour);
			mlx_put_pixel(img, x + xy.x, y + xy.y, colour);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_mini_map(t_game game)
{
	int		xsteps;
	int		ysteps;
	size_t	y;
	size_t	x;
	t_cords_int32	yx;
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
			yx.y = y * ysteps;
			yx.x = x * xsteps;
			if (game.map.tiles[y][x] == '1')
			{
				// printf("%s %d yx.y %f yx.x %f\n", __FILE__, __LINE__, yx.y, yx.x) ;
				pixset_yx_height_width(game.minimap, get_rgba(0, 77, 77, 255),
					yx, height_width);
				// ft_memset(game.minimap->pixels, get_rgba(0, 77, 77, 255), 
				// 	game.minimap->width * game.minimap->height * sizeof(int32_t));
				// mlx_image_to_window(game.mlx, game.minimap,x*1000,y*1000);
			}
			if (game.map.tiles[y][x] == '0')
			{
				pixset_yx_height_width(game.minimap, get_rgba(0, 255, 255, 255),
					yx, height_width);
			}
			x += 1;
			
		}
		x = 0;
		y += 1;
	}
	if (mlx_image_to_window(game.mlx, game.minimap,0,0) < 0)
	{
		ft_error("Error\nImage didn't arrive at window", 1, &game);
	}
	printf("%s %d draw miniplayer\n", __FILE__, __LINE__);
	// draw_mini_player(game);
	printf("%s %d\n", __FILE__, __LINE__);
	// if max size bigger 100 / 10 if bigger 1000 / 100...
	mlx_resize_image(game.minimap, game.bg->width/2, game.bg->height/2);
}

// void	draw_mini_player(t_game game)
// {
// 	t_cords_int32	yx;
// 	t_height_width	height_width;
// // printf("%s %d\n", __FILE__, __LINE__);
// printf("%s %d img height%u img width %u\n", __FILE__, __LINE__, game.img->height,game.img->width);
// 	// game.miniplayer= mlx_new_image(game.mlx, game.img->width/10, game.img->width/10);
// 	game.miniplayer= mlx_new_image(game.mlx, game.img->width, game.img->width);
// 	printf("%s %d mini height %u mini width %u\n", __FILE__, __LINE__, game.miniplayer->height,game.miniplayer->width);
// 	printf("%s %d img.y %u img.x %u\n", __FILE__, __LINE__, game.img->instances->y,game.img->instances->x);
// 	// game.miniplayer->instances->x = game.img->instances->x;
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	// game.miniplayer->instances->y = game.img->instances->y;
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	// yx.x = game.miniplayer->instances->x;
// 	yx.x = game.img->instances->x;
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	// yx.y = game.miniplayer->instances->y;
// 	yx.y = game.img->instances->y;
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	// printf("%s %d\n", __FILE__, __LINE__);ß
// 	printf("%s %d yx.y %u yx.x %u\n", __FILE__, __LINE__, yx.y, yx.x);
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	height_width.height = game.miniplayer->height;
	
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	height_width.width = game.miniplayer->width;
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	// i draw the player onto the minimap and then just draw that one single 
// 	// image to window
// 	pixset_yx_height_width(game.miniplayer, get_rgba(0, 200, 0, 255),
// 					yx, height_width);
// 	// pixset_yx_height_width(game.minimap, get_rgba(0, 200, 0, 255),
// 	// 				yx, height_width);
// 	if (mlx_image_to_window(game.mlx, game.miniplayer,0,0) < 0)
// 	{
// 		ft_error("Error\nImage didn't arrive at window", 1, &game);
// 	}
// }

// void	draw_mini_player(t_game game)
// {
// 	// printf("%s %d draw mini player\n", __FILE__, __LINE__) ;
// 	t_height_width height_width;
// 	height_width.height = 10;
// 	height_width.width = 10;
// 	game.miniplayer = mlx_new_image(game.mlx, height_width.width, height_width.height);
// 	if (!game.miniplayer)
// 		ft_error("Error\nImage didn't create", 1, &game);
// 	// ft_memset(game.miniplayer->pixels, get_rgba(0, 200, 0, 250), ((game.img->width)) * ((game.img->height)) * sizeof(int32_t));
// 	t_cords_int32 xy;
// 	xy.x = 1;
// 	xy.y = 1;
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	pixset_yx_height_width(game.miniplayer, get_rgba(0, 200, 0, 255), xy, height_width);
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	if (mlx_image_to_window(game.mlx, game.miniplayer, 0, 0) < 0)
// 		ft_error("Error\nImage didn't arrive at window", 1, &game);
// 		// printf("%s %d\n", __FILE__, __LINE__);
// }

void	draw_mini_player(t_game *game)
{
	int		xsteps;
	int		ysteps;
	size_t	y;
	size_t	x;
	t_cords_int32	yx;
	t_height_width	height_width;

	xsteps = 10;
	ysteps = 10;
	height_width.height = ysteps;
	height_width.width = xsteps;
	y = 0;
	x = 0;
	
	// game.minimap = mlx_new_image(game.mlx, game.map.max_x * xsteps, game.map.max_y * ysteps);
	// game.miniplayer = mlx_new_image(game.mlx, game.map.max_x * xsteps, game.map.max_y * ysteps);
	// game.miniplayer = mlx_new_image(game.mlx, xsteps, ysteps);
	game->miniplayer = mlx_new_image(game->mlx, game->img->width, game->img->height);
	if (!game->miniplayer)
		ft_error("Error\nImage didn't create", 1, game);
	// while (game.map.tiles[y] != NULL)
	// {
		// while (game.map.tiles[y][x] != 0)
		// {
			yx.y = y * ysteps;
			yx.x = x * xsteps;
			// if (game.map.tiles[y][x] == '1')
			// {
				// pixset_yx_height_width(game.minimap, get_rgba(0, 77, 77, 255),
				// 	yx, height_width);
				// pixset_yx_height_width(game.minimap, get_rgba(0, 200, 0, 255),
				// 	yx, height_width);
				pixset_yx_height_width(game->miniplayer, get_rgba(0, 200, 0, 255),
					yx, height_width);
			// }
			// if (game.map.tiles[y][x] == '0')
			// {
			// 	pixset_yx_height_width(game.minimap, get_rgba(0, 255, 255, 255),
			// 		yx, height_width);
			// }
			// x += 1;
			
		// }
		// x = 0;
		// y += 1;
	// }

	// if (mlx_image_to_window(game.mlx, game.minimap,0,0) < 0)
	// if (mlx_image_to_window(game.mlx, game.miniplayer,0,0) < 0)
	printf("%s %d img.y %u img.x %u\n", __FILE__, __LINE__, game->img->instances->y,game->img->instances->x);
	if (mlx_image_to_window(game->mlx, game->miniplayer, game->img->instances->x, game->img->instances->y) < 0)
	{
		ft_error("Error\nImage didn't arrive at window", 1, game);
	}
	if (!game->miniplayer->instances)
	{
    	ft_error("Error: miniplayer instances is still NULL after mlx_image_to_window", 1, game);
	}
	game->miniplayer->instances->x = game->img->instances->x/10;
	game->miniplayer->instances->y = game->img->instances->y/10;
	printf("%s %d mini.y %u mini.x %u\n", __FILE__, __LINE__, game->miniplayer->instances->y,game->miniplayer->instances->x);
	// printf("%s %d draw miniplayer\n", __FILE__, __LINE__);
	// draw_mini_player(game);
	// printf("%s %d\n", __FILE__, __LINE__);
	// if max size bigger 100 / 10 if bigger 1000 / 100...
	// mlx_resize_image(game.minimap, game.bg->width/2, game.bg->height/2);
	mlx_resize_image(game->miniplayer, game->img->width/2, game->img->height/2);
}