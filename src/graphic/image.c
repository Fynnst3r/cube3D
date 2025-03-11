/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/03/11 19:52:15 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	draw_mini_map(t_game game);
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

void	draw_line(t_game *game)
{
	t_cords_int32	yx;
	t_height_width	height_width;
	float			x_diff;
	float			y_diff;
	float			slope;
	int	x = game->miniplayer->instances->x;
	int	y = game->miniplayer->instances->y;
	printf("%s %d x %d \n", __FILE__, __LINE__, x);
	printf("%s %d y %d \n", __FILE__, __LINE__, y);
	game->dir_x = (game->player.pos.x + game->player.dir.x)* MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
	game->dir_y = (game->player.pos.y + game->player.dir.y)* MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
	printf("%s %d dir        x %f\n", __FILE__, __LINE__, game->dir_x);
	printf("%s %d dir        y %f\n", __FILE__, __LINE__, game->dir_y);
	x_diff = game->dir_x - game->miniplayer->instances->x;
	y_diff = game->dir_y - game->miniplayer->instances->y;
	printf("%s %d x diff %f  y diff %f \n", __FILE__, __LINE__, x_diff, y_diff);
	slope = y_diff / x_diff;
	if (x_diff < 0)
		x_diff *= -1;
	if (y_diff < 0)
		y_diff *= -1;
	printf("%s %d slope %f\n", __FILE__, __LINE__, slope);
	height_width.width = 1;
	height_width.height = 1;
	game->line = mlx_new_image(game->mlx, (x_diff + height_width.width) * MINI_UNITS_PER_TILE,
		 (y_diff + height_width.height) * MINI_UNITS_PER_TILE);
	if (!game->line)
		ft_error("mlx_new_image for game->line unsuccessful\n", 42, game);
	if (game->dir_x > game->miniplayer->instances->x && game->dir_y >= game->miniplayer->instances->y )
	{
		printf("%s %d\n", __FILE__, __LINE__);
		while (x <= game->dir_x)
		{
			printf("%s %d x %d \n", __FILE__, __LINE__, x);
			y = slope * (x - game->miniplayer->instances->x) + game->miniplayer->instances->y;
			printf("%s %d y %d\n", __FILE__, __LINE__, y);
			yx.x = x;
			yx.y = y;
			printf("%s %d\n", __FILE__, __LINE__);
			pixset_yx_height_width(game->line, get_rgba(0, 0, 0, 255), yx, height_width);
			printf("%s %d\n", __FILE__, __LINE__);
			x++;
		}
	}
	printf("%s %d\n", __FILE__, __LINE__);
	mlx_image_to_window(game->mlx, game->line, 0, 0);
	printf("%s %d\n", __FILE__, __LINE__);
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
	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
	ft_mlx_draw_pixel(pixelstart, color);
}

void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
	t_height_width height_width)
{
	u_int32_t x = 0;
	u_int32_t y = 0;
	while (y < height_width.height)
	{
		while (x < height_width.width)
		{
			mlx_put_pixel(img, x + xy.x, y + xy.y, colour);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_mini_map(t_game game)
{
	size_t	y;
	size_t	x;
	t_cords_int32	yx;
	t_height_width	height_width;

	height_width.height = MINI_UNITS_PER_TILE;
	height_width.width = MINI_UNITS_PER_TILE;
	y = 0;
	x = 0;
	printf("%s %d map max y %zu  map max x %zu\n", __FILE__, __LINE__, game.map.max_y, game.map.max_x);
	game.minimap = mlx_new_image(game.mlx, game.map.max_x * MINI_UNITS_PER_TILE,
		game.map.max_y * MINI_UNITS_PER_TILE);
	while (game.map.tiles[y] != NULL)
	{
		while (game.map.tiles[y][x] != 0)
		{
			yx.y = y * MINI_UNITS_PER_TILE;
			yx.x = x * MINI_UNITS_PER_TILE;
			if (game.map.tiles[y][x] != '0' && game.map.tiles[y][x] != ' ')
			{
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
	mlx_resize_image(game.minimap, game.minimap->width * MINI_RESIZE_FACTOR,
		game.minimap->height * MINI_RESIZE_FACTOR);
}

void	draw_mini_player(t_game *game)
{
	t_cords_int32	yx;
	t_height_width	height_width;

	height_width.height = MINI_UNITS_PER_TILE;
	height_width.width = MINI_UNITS_PER_TILE;
	game->miniplayer = mlx_new_image(game->mlx, MINI_PLAYER_WIDTH,
		MINI_PLAYER_HEIGHT);
	if (!game->miniplayer)
		ft_error("Error\nImage didn't create", 1, game);
	yx.y = 0;
	yx.x = 0;
	pixset_yx_height_width(game->miniplayer, get_rgba(0, 200, 0, 255), yx,
		height_width);
	if (mlx_image_to_window(game->mlx, game->miniplayer,
			game->player.pos.x * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE,
			game->player.pos.y * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE) < 0)
	{
		ft_error("Error\nImage didn't arrive at window", 1, game);
	}
	game->miniplayer->instances->x = game->player.pos.x * MINI_UNITS_PER_TILE;
	game->miniplayer->instances->y = game->player.pos.y * MINI_UNITS_PER_TILE;
	printf("%s %d mini x %d  mini y %d\n", __FILE__, __LINE__, game->miniplayer->instances->x, game->miniplayer->instances->y);
	mlx_resize_image(game->miniplayer, MINI_PLAYER_WIDTH * MINI_RESIZE_FACTOR,
			MINI_PLAYER_HEIGHT * MINI_RESIZE_FACTOR);
}
