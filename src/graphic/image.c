/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/03/18 14:46:34 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_mini_map(t_game *game);
void	draw_mini_player(t_game *game);
void	draw_line(t_game *game);
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

// void	draw_line(t_game *game)
// {
// 	t_cords_int32	yx;
// 	t_height_width	height_width;
// 	float			x_diff;
// 	float			y_diff;
// 	float			slope;
// 	// game->img->instances->x = 10;
// 	// game->img->instances->y = 100;
// 	// int	x = game->img->instances->x;
// 	// int	y = game->img->instances->y;
// 	// int	x = game->player.pos.x;
// 	// int	y = game->player.pos.y;
// 	int	x = game->miniplayer->instances->x;
// 	int	y = game->miniplayer->instances->y;
// 	printf("%s %d x %d \n", __FILE__, __LINE__, x);
// 	printf("%s %d y %d \n", __FILE__, __LINE__, y);

// 	// xstart < xend  ystart < yends => top left to bottom right
// 	// game.dir_x = 100;
// 	// game.dir_y = 80;

// 	// xstart > xend  ystart < yend => top right to bottom left
// 	// game->dir_x = 1;
// 	// game->dir_y = 80;

// 	// // xstart < xend  ystart > yend => botom left to top right
// 	// game->dir_x = 100;
// 	// game->dir_y = 8;
// 	printf("%s %d dir big    x %f\n", __FILE__, __LINE__, game->player.dir.x);
// 	printf("%s %d dir big    y %f\n", __FILE__, __LINE__, game->player.dir.y);
// 	// game->dir_x = (game->player.pos.x + game->player.dir.x)* MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
// 	// game->dir_y = (game->player.pos.y + game->player.dir.y)* MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
// 	// game->dir_x = (game->player.pos.x + game->player.dir.x) * MINI_UNITS_PER_TILE;
// 	// game->dir_y = (game->player.pos.y + game->player.dir.y) * MINI_UNITS_PER_TILE;
// 	game->dir_x = (x + game->player.dir.x * MINI_UNITS_PER_TILE);
// 	game->dir_y = (y + game->player.dir.y * MINI_UNITS_PER_TILE);
// 	printf("%s %d dir        x %f\n", __FILE__, __LINE__, game->dir_x);
// 	printf("%s %d dir        y %f\n", __FILE__, __LINE__, game->dir_y);
// 	// x_diff = game->dir_x - game->img->instances->x;
// 	// y_diff = game->dir_y - game->img->instances->y;
// 	// x_diff = game->dir_x - game->player.pos.x;
// 	// y_diff = game->dir_y - game->player.pos.y;
// 	x_diff = game->dir_x - game->miniplayer->instances->x;
// 	y_diff = game->dir_y - game->miniplayer->instances->y;
// 	// printf("%s %d x diff %d  y diff %d \n", __FILE__, __LINE__, x_diff, y_diff);
// 	// printf("%s %d\n", __FILE__, __LINE__);
// 	printf("%s %d x diff %f  y diff %f \n", __FILE__, __LINE__, x_diff, y_diff);
// 	slope = y_diff / x_diff;
// 	if (x_diff < 0)
// 		x_diff *= -1;
// 	if (y_diff < 0)
// 		y_diff *= -1;
// 	// printf("%s %d slope %d\n", __FILE__, __LINE__, slope);
// 	printf("%s %d slope %f\n", __FILE__, __LINE__, slope);
// 	height_width.width = MINI_LINE_WIDTH;
// 	height_width.height = MINI_LINE_WIDTH;
// 	// game->line = mlx_new_image(game->mlx, x_diff, y_diff);
// 	// game->line = mlx_new_image(game->mlx, x_diff * 10, y_diff * 10);
// 	// printf("%s %d xdiff + height * ")
// 	game->line = mlx_new_image(game->mlx, (x_diff + height_width.width) * MINI_UNITS_PER_TILE,
// 		 (y_diff + height_width.height) * MINI_UNITS_PER_TILE);
// 	if (!game->line)
// 		ft_error("mlx_new_image for game->line unsuccessful\n", 42, game);
// 	// xstart < xend  ystart < yends => top left to bottom right
// 	// if (game->dir_x > game->img->instances->x && game->dir_y > game->img->instances->y )
// 	// if (game->dir_x > game->player.pos.x && game->dir_y > game->player.pos.y )
// 	if (game->dir_x > game->miniplayer->instances->x && game->dir_y >= game->miniplayer->instances->y )
// 	{
// 		printf("%s %d\n", __FILE__, __LINE__);
// 		while (x <= game->dir_x)
// 		{
// 			printf("%s %d x %d \n", __FILE__, __LINE__, x);
// 			// y = slope * (x - game->img->instances->x) + game->img->instances->y;
// 			// y = slope * (x - game->player.pos.x) + game->player.pos.y ;
// 			y = slope * (x - game->miniplayer->instances->x) + game->miniplayer->instances->y;
// 			printf("%s %d y %d\n", __FILE__, __LINE__, y);
// 			// mlx_put_pixel(game.line, x, y, get_rgba(255, 255, 0, 255));
// 			yx.x = x;
// 			yx.y = y;
// 			printf("%s %d\n", __FILE__, __LINE__);
// 			pixset_yx_height_width(game->line, get_rgba(222, 222, 0, 255), yx, height_width);
// 			// pixset_yx_height_width(game->line, get_rgba(0, 0, 0, 255), yx, height_width);
// 			printf("%s %d\n", __FILE__, __LINE__);
// 			// mlx_image_to_window(game->mlx, game->line, game->miniplayer->instances->x, game->miniplayer->instances->y);
// 			x++;
// 		}
// 	}
// 	// xstart > xend  ystart < yend => top right to bottom left
// 	// if (game->dir_x < game->img->instances->x && game->dir_y > game->img->instances->y )
// 	// {
// 	// 	printf("%s %d\n", __FILE__, __LINE__);
// 	// 	while (x >= game->dir_x)
// 	// 	{
// 	// 		// y = slope * (x - game->img->instances->x) + game->img->instances->y;
// 	// 		y = slope * (x - game->img->instances->x) + game->img->instances->y;
// 	// 		// mlx_put_pixel(game.line, x, y, get_rgba(255, 255, 0, 255));
// 	// 		yx.x = x;
// 	// 		yx.y = y;
// 	// 		pixset_yx_height_width(game->line, get_rgba(255, 255, 0, 255), yx, height_width);
// 	// 		x--;
// 	// 	}
// 	// }
// 	// // // xstart < xend  ystart > yend => botom left to top right
// 	// if (game->dir_x > game->img->instances->x && game->dir_y < game->img->instances->y )
// 	// {
// 	// 	printf("%s %d\n", __FILE__, __LINE__);
// 	// 	while (x <= game->dir_x)
// 	// 	{
// 	// 		printf("%s %d x %d \n", __FILE__, __LINE__, x);
// 	// 		y = game->img->instances->y + slope * (x - game->img->instances->x);
// 	// 		printf("%s %d y %d\n", __FILE__, __LINE__, y);
// 	// 		// mlx_put_pixel(game.line, x, y, get_rgba(255, 255, 0, 255));
// 	// 		yx.x = x;
// 	// 		yx.y = y;
// 	// 		// printf("%s %d\n", __FILE__, __LINE__);
// 	// 		pixset_yx_height_width(game->line, get_rgba(111, 222, 2, 255), yx, height_width);
// 	// 		// printf("%s %d\n", __FILE__, __LINE__);
// 	// 		x++;
// 	// 	}
// 	// }
// 	printf("%s %d line width %d height %d\n", __FILE__, __LINE__, game->line->width, game->line->height);
// 	// mlx_image_to_window(game->mlx, game->line, game->dir_x, game->dir_y);
// 	// mlx_image_to_window(game->mlx, game->line, game->miniplayer->instances->x, game->miniplayer->instances->y);
// 	mlx_image_to_window(game->mlx, game->line, 0, 0);
// 	// mlx_resize_image(game->line, game->line->width * MINI_RESIZE_FACTOR,
// 	// 	game->line->height * MINI_RESIZE_FACTOR);
// 	// mlx_resize_image(game->line, game->line->width,
// 	// 	game->line->height);
// 	printf("%s %d\n", __FILE__, __LINE__);
// }
void	draw_line(t_game *game)
{
	int				x;
	int				y;
	t_cords_int32	yx;
	t_height_width	height_width;
	float			x_diff;
	float			y_diff;
	float			slope;

	// printf("%s %d           \n", __FILE__, __LINE__);
	if (game->line != NULL)
	{
		mlx_delete_image(game->mlx, game->line);
	}
	// printf("%s %d           \n", __FILE__, __LINE__);
	// x = game->miniplayer->instances->x;
	// y = game->miniplayer->instances->y;
	x = game->miniplayer->instances->x * MINI_RESIZE_FACTOR;
	y = game->miniplayer->instances->y * MINI_RESIZE_FACTOR;
	printf("%s %d start     x %d  y %d\n", __FILE__, __LINE__, x, y);
	// x = game->player.pos.x * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
	// y = game->player.pos.y * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
	height_width.height = MINI_LINE_HEIGHT;
	height_width.width = MINI_LINE_WIDTH;
	game->dir_x = (x + game->player.dir.x * MINI_UNITS_PER_TILE * MINI_RAY_LENGRH);
	game->dir_y = (y + game->player.dir.y * MINI_UNITS_PER_TILE * MINI_RAY_LENGRH);
	printf("%s %d dir big    x %f\n", __FILE__, __LINE__, game->player.dir.x);
	printf("%s %d dir big    y %f\n", __FILE__, __LINE__, game->player.dir.y);
	printf("%s %d dir        x %f\n", __FILE__, __LINE__, game->dir_x);
	printf("%s %d dir        y %f\n", __FILE__, __LINE__, game->dir_y);
	x_diff = game->dir_x - game->miniplayer->instances->x;
	y_diff = game->dir_y - game->miniplayer->instances->y;
	// x_diff = game->dir_x - (game->player.pos.x * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE);
	// y_diff = game->dir_y - (game->player.pos.y * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE);
	printf("%s %d x diff %f  y diff %f \n", __FILE__, __LINE__, x_diff, y_diff);
	slope = y_diff / x_diff;
	// printf("%s %d           \n", __FILE__, __LINE__);
	printf("%s %d slope %f\n", __FILE__, __LINE__, slope);
	if (x_diff < 0)
			x_diff *= -1;
		if (y_diff < 0)
			y_diff *= -1;
	// printf("%s %d (x_diff + height_width.width) * MINI_UNITS_PER_TILE %f\n", __FILE__, __LINE__, (x_diff + height_width.width) * MINI_UNITS_PER_TILE);
	// printf("%s %d (y_diff + height_width.heigth) * MINI_UNITS_PER_TILE %f\n", __FILE__, __LINE__, (y_diff + height_width.height) * MINI_UNITS_PER_TILE);
	// printf("%s %d (x_diff + height_width.width) %f\n", __FILE__, __LINE__, (x_diff + height_width.width) );
	// printf("%s %d (y_diff + height_width.heigth) %f\n", __FILE__, __LINE__, (y_diff + height_width.height) );
	// game->line = mlx_new_image(game->mlx, (x_diff + height_width.width) * MINI_UNITS_PER_TILE,
	// 				(y_diff + height_width.height) * MINI_UNITS_PER_TILE);
	// printf("%s %d           \n", __FILE__, __LINE__);
	game->line = mlx_new_image(game->mlx, (x_diff + height_width.width),
		(y_diff + height_width.height));
	if (!game->line)
		ft_error("mlx_new_image for game->line unsuccessful\n", 42, game);
	printf("%s %d new img height %d width %d\n", __FILE__, __LINE__, game->line->height, game->line->width);
	// printf("%s %d           \n", __FILE__, __LINE__);
	// xstart < xend  ystart < yends => top left to bottom right
	if (game->dir_x > game->miniplayer->instances->x && game->dir_y >= game->miniplayer->instances->y )
	{
		printf("%s %d           \n", __FILE__, __LINE__);
		while (x <= game->dir_x)
		{
			if (slope)
				y = slope * (x - game->miniplayer->instances->x) + game->miniplayer->instances->y;
			printf("%s %d            x %d\n", __FILE__, __LINE__, x);
			printf("%s %d            y %d\n\n", __FILE__, __LINE__, y);
			// yx.x = x;
			// yx.y = y;
			yx.x = x - game->miniplayer->instances->x;
			yx.y = y - game->miniplayer->instances->y;
			printf("%s %d           \n", __FILE__, __LINE__);
			pixset_yx_height_width(game->line, get_rgba(222, 222, 0, 255), yx, height_width);
			printf("%s %d           \n", __FILE__, __LINE__);
			x++;
		}
	}
	// xstart > xend  ystart < yend => top right to bottom left
	if (game->dir_x < game->img->instances->x && game->dir_y > game->img->instances->y )
	{
		printf("%s %d\n", __FILE__, __LINE__);
		while (x >= game->dir_x)  
		{
			if (slope)
				// y = slope * (x - game->img->instances->x) + game->img->instances->y;
				y = slope * (x - game->img->instances->x) + game->img->instances->y;
			yx.x = x - game->miniplayer->instances->x;
			yx.y = y - game->miniplayer->instances->y;
			pixset_yx_height_width(game->line, get_rgba(222, 222, 2, 222), yx, height_width);
			x--;
		}
	}
	// xstart < xend  ystart > yend => botom left to top right
	if (game->dir_x > game->img->instances->x && game->dir_y < game->img->instances->y )
	{
		printf("%s %d\n", __FILE__, __LINE__);
		while (x <= game->dir_x)
		{
			printf("%s %d\n", __FILE__, __LINE__);
			if (slope)
				// y = game->img->instances->y + slope * (x - game->img->instances->x);
				y = slope * (x - game->miniplayer->instances->x) + game->miniplayer->instances->y;
			printf("%s %d x %d \n", __FILE__, __LINE__, x);
			printf("%s %d y %d\n", __FILE__, __LINE__, y);
			yx.x = x - game->miniplayer->instances->x;
			yx.y = y - game->miniplayer->instances->y;
			printf("%s %d\n", __FILE__, __LINE__);
			pixset_yx_height_width(game->line, get_rgba(222, 222, 2, 222), yx, height_width);
			printf("%s %d\n", __FILE__, __LINE__);
			x++;
		}
	}
	// xstart > xend  ystart > yend => botom right to top left
	if (game->dir_x < game->img->instances->x && game->dir_y < game->img->instances->y )
	{
		printf("%s %d\n", __FILE__, __LINE__);
		while (x >= game->dir_x)  
		{
			if (slope)
				// y = slope * (x - game->img->instances->x) + game->img->instances->y;
				y = slope * (x - game->img->instances->x) - game->img->instances->y;
			yx.x = x - game->miniplayer->instances->x;
			yx.y = y - game->miniplayer->instances->y;
			pixset_yx_height_width(game->line, get_rgba(222, 222, 2, 222), yx, height_width);
			x--;
		}
	}
	// printf("%s %d           \n", __FILE__, __LINE__);
	// yx.y = 0;
	// yx.x = 0;
	// pixset_yx_height_width(game->line, get_rgba(222, 222, 0, 255), yx,
	// 	height_width);
	if (mlx_image_to_window(game->mlx, game->line,
		game->miniplayer->instances->x, game->miniplayer->instances->y) < 0)
		{
			ft_error("Error\nImage didn't arrive at window", 1, game);
		}
	game->line->instances->x = game->miniplayer->instances->x;
	game->line->instances->y = game->miniplayer->instances->y;
		// mlx_resize_image(game->line, game->line->width * MINI_RESIZE_FACTOR,
		// 	game->line->height * MINI_RESIZE_FACTOR);
	// pixset_yx_height_width(game->line, 0, yx, height_width);
	// printf("%s %d mini x %d  mini y %d\n", __FILE__, __LINE__, game->line->instances->x, game->line->instances->y);
}

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
	while (y < height_width.height)
	{
		printf("%s %d y %u x %u\n", __FILE__, __LINE__, y, x) ;
		// printf("%s %d xy.y %u xy.x %u\n", __FILE__, __LINE__, xy.y, xy.x) ;
		// printf("%s %d xy.y + y %u xy.x + x %u\n", __FILE__, __LINE__, xy.y + y, xy.x + x) ;
		while (x < height_width.width)
		{
			// printf("%s %d xy.y %f xy.x %f\n", __FILE__, __LINE__, xy.y, xy.x) ;
			printf("%s %d xy.y %d xy.x %d\n", __FILE__, __LINE__, xy.y, xy.x) ;
			printf("%s %d xy.y + y %u xy.x + x %u\n", __FILE__, __LINE__, xy.y + y, xy.x + x) ;
			// printf("%s %d y %u x %u\n", __FILE__, __LINE__, y, x) ;
			// mlx_put_pixel(img, xy.x, xy.y, colour);
			// ft_mlx_put_pixel(img, x + xy.x, y + xy.y, colour);
			mlx_put_pixel(img, x + xy.x, y + xy.y, colour);
			// mlx_put_pixel(img, x, y, colour);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_mini_map(t_game *game)
{
	size_t	y;
	size_t	x;
	t_cords_int32	yx;
	t_height_width	height_width;

	height_width.height = MINI_UNITS_PER_TILE;
	height_width.width = MINI_UNITS_PER_TILE;
	y = 0;
	x = 0;
			// printf("%s %d            \n\n", __FILE__, __LINE__);
	// printf("%s %d map max y %zu  map max x %zu\n", __FILE__, __LINE__, game->map.max_y, game->map.max_x);
	game->minimap = mlx_new_image(game->mlx, game->map.max_x * MINI_UNITS_PER_TILE,
		game->map.max_y * MINI_UNITS_PER_TILE);
		// printf("%s %d            map tile y = 0  %s\n\n", __FILE__, __LINE__, game->map.tiles[y]);
	while (game->map.tiles[y] != NULL)
	{
		while (game->map.tiles[y][x] != 0)
		{
			yx.y = y * MINI_UNITS_PER_TILE;
			yx.x = x * MINI_UNITS_PER_TILE;
			if (game->map.tiles[y][x] != '0' && game->map.tiles[y][x] != ' ')
			{
				// printf("%s %d yx.y %f yx.x %f\n", __FILE__, __LINE__, yx.y, yx.x) ;
				pixset_yx_height_width(game->minimap, get_rgba(0, 77, 77, 255),
					yx, height_width);
				// ft_memset(game->minimap->pixels, get_rgba(0, 77, 77, 255), 
				// 	game->minimap->width * game->minimap->height * sizeof(int32_t));
				// mlx_image_to_window(game->mlx, game->minimap,x*1000,y*1000);
			}
			if (game->map.tiles[y][x] == '0')
			{
				pixset_yx_height_width(game->minimap, get_rgba(0, 255, 255, 255),
					yx, height_width);
					
			}
			x += 1;
			
		}
		x = 0;
		y += 1;
	}
	// if (mlx_image_to_window(game->mlx, game->minimap,0,0) < 0)
	// {
	// 	ft_error("Error\nImage didn't arrive at window", 1, &game->;
	// }
	// printf("%s %d draw miniplayer\n", __FILE__, __LINE__);
	// draw_mini_player(game->;
	// if max size bigger 100 / 10 if bigger 1000 / 100...
	// mlx_resize_image(game->minimap, game->bg->width/MINI_RESIZE_FACTOR,
	// 	game->bg->height/MINI_RESIZE_FACTOR);
	// mlx_resize_image(game->minimap, game->minimap->width * MINI_RESIZE_FACTOR,
	// 	game->minimap->height * MINI_RESIZE_FACTOR);
}
void	draw_mini_player(t_game *game)
{
	t_cords_int32	yx;
	t_height_width	height_width;

	height_width.height = MINI_UNITS_PER_TILE;
	height_width.width = MINI_UNITS_PER_TILE;
	if (game->miniplayer)
		mlx_delete_image(game->mlx, game->miniplayer);
	game->miniplayer = mlx_new_image(game->mlx, MINI_PLAYER_WIDTH,
		MINI_PLAYER_HEIGHT);
	if (!game->miniplayer)
		ft_error("Error\nImage didn't create", 1, game);
	yx.y = 0;
	yx.x = 0;
	// pixset_yx_height_width(game->miniplayer, get_rgba(0, 200, 0, 255), yx,
	// 	height_width);
	pixset_yx_height_width(game->miniplayer, 0, yx, height_width);
	// printf("%s %d player x * resize * units %f\n", __FILE__, __LINE__, game->player.pos.x * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE);
	// if (mlx_image_to_window(game->mlx, game->miniplayer,
	// 		game->player.pos.x * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE,
	// 		game->player.pos.y * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE) < 0)
	if (mlx_image_to_window(game->mlx, game->miniplayer,
		game->player.pos.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR,
		game->player.pos.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR) < 0)
	{
		ft_error("Error\nImage didn't arrive at window", 1, game);
	}
	game->miniplayer->instances->x = game->player.pos.x * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
	game->miniplayer->instances->y = game->player.pos.y * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
	// game->miniplayer->instances->x = game->player.pos.x * MINI_UNITS_PER_TILE;
	// game->miniplayer->instances->y = game->player.pos.y * MINI_UNITS_PER_TILE;
	// printf("%s %d mini x %d  mini y %d\n", __FILE__, __LINE__, game->miniplayer->instances->x, game->miniplayer->instances->y);
	// printf("%s %d mini width %d mini heigth %d\n", __FILE__, __LINE__, game->miniplayer->width, game->miniplayer->height);
	mlx_resize_image(game->miniplayer, game->miniplayer->width * MINI_RESIZE_FACTOR,
		game->miniplayer->height * MINI_RESIZE_FACTOR);
}