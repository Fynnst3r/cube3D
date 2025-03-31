/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/03/31 02:07:08 by nsloniow         ###   ########.fr       */
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

void draw_cone(t_game *game)
{
    double start_x = game->player.pos.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
    double start_y = game->player.pos.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;

    int num_lines = 50;  // Number of lines in the cone
    double cone_angle = 0.01;  // The amount by which we shift each line (in radians)
	
	double			x;
	double			y;
	x = game->player.pos.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	y = game->player.pos.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	game->dir_x = (x + game->player.dir.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR * MINI_RAY_LENGRH);
	game->dir_y = (y + game->player.dir.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR * MINI_RAY_LENGRH);
	printf("%s %d dir big    x %f\n", __FILE__, __LINE__, game->player.dir.x);
	printf("%s %d dir big    y %f\n", __FILE__, __LINE__, game->player.dir.y);
	printf("%s %d dir        x %f\n", __FILE__, __LINE__, game->dir_x);
	printf("%s %d dir        y %f\n", __FILE__, __LINE__, game->dir_y);
    // Draw the original line first
    // double end_x = game->dir_x;
    // double end_y = game->dir_y;
    // draw_line(game);
    
	// draw cone
	int lines_per_side_off_direction_line = -num_lines/2;
    // draw additional lines to form a cone
	
	// half on the left side, half on the right side
    while ( lines_per_side_off_direction_line <= num_lines / 2 ) 
    {
        // Calculate the new angle for each cone line
        double angle = atan2(game->player.dir.y, game->player.dir.x) +
						( lines_per_side_off_direction_line * cone_angle);
        
        // Calculate the direction vector for this new angle
        game->dir_x = start_x + cos(angle) * MINI_RAY_LENGRH * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
        game->dir_y = start_y + sin(angle) * MINI_RAY_LENGRH * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
        draw_line(game);
		lines_per_side_off_direction_line++;
    }
}

void	draw_line(t_game *game)
{
	double			start_x;
	double			start_y;
	double			x;
	double			y;
	t_cords_int32	yx;
	t_height_width	height_width;
	double			x_diff;
	double			y_diff;
	double			slope;
	int				r = 111;
	int				g = 11;
	int				b = 11;
	// int				a = 125;
	int				a = 255;

	printf("%s %d           \n", __FILE__, __LINE__);
	start_x = game->player.pos.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	start_y = game->player.pos.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	x = game->player.pos.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	y = game->player.pos.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	// printf("%s %d start     x %d  y %d\n", __FILE__, __LINE__, x, y);
	printf("%s %d start     x %f  y %f\n", __FILE__, __LINE__, x, y);
	height_width.height = MINI_LINE_HEIGHT;
	height_width.width = MINI_LINE_WIDTH;
	// game->dir_x = (x + game->player.dir.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR * MINI_RAY_LENGRH);
	// game->dir_y = (y + game->player.dir.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR * MINI_RAY_LENGRH);
	// printf("%s %d dir big    x %f\n", __FILE__, __LINE__, game->player.dir.x);
	// printf("%s %d dir big    y %f\n", __FILE__, __LINE__, game->player.dir.y);
	// printf("%s %d dir        x %f\n", __FILE__, __LINE__, game->dir_x);
	// printf("%s %d dir        y %f\n", __FILE__, __LINE__, game->dir_y);
	x_diff = game->dir_x - x;
	y_diff = game->dir_y - y;
	// printf("%s %d x diff %f  y diff %f \n", __FILE__, __LINE__, x_diff, y_diff);
	// printf("%s %d new minimap height %d width %d\n", __FILE__, __LINE__, game->minimap->height, game->minimap->width);
	if (fabs(x_diff) > fabs(y_diff))
	{
		if (x_diff == 0)
			slope = 0;
		else
			slope = y_diff / x_diff;
		// printf("%s %d slope %f\n", __FILE__, __LINE__, slope);
		if (x_diff > 0)
			while (x <= game->dir_x)
			{
				y = round(slope * (x - start_x) + start_y);
				yx.x = (int32_t)x;
				yx.y = (int32_t)y;
				// printf("%s %d            x %d\n", __FILE__, __LINE__, yx.x);
				// printf("%s %d            y %d\n\n", __FILE__, __LINE__, yx.y);
				pixset_yx_height_width(game->minimap, get_rgba(r, g, b, a), yx, height_width);
				x++;
			}
		if (x_diff < 0)
			while (x >= game->dir_x)
			{
					y = round(slope * (x - start_x) + start_y);
				yx.x = (int32_t)x;
				yx.y = (int32_t)y;
				// printf("%s %d            x %d\n", __FILE__, __LINE__, yx.x);
				// printf("%s %d            y %d\n\n", __FILE__, __LINE__, yx.y);
				pixset_yx_height_width(game->minimap, get_rgba(r, g, b, a), yx, height_width);
				x--;
			}
	}
	else
	{
		if (y_diff == 0)
			slope = 0;
		else
			slope = x_diff / y_diff;
		printf("%s %d slope %f\n", __FILE__, __LINE__, slope);
		if (y_diff > 0)
			while (y <= game->dir_y)
			{
				x = round(slope * (y - start_y) + start_x);
				yx.x = (int32_t)x;
				yx.y = (int32_t)y;
				// printf("%s %d            x %d\n", __FILE__, __LINE__, yx.x);
				// printf("%s %d            y %d\n\n", __FILE__, __LINE__, yx.y);
				pixset_yx_height_width(game->minimap, get_rgba(r, g, b, a), yx, height_width);
				y++;
			}
		if (y_diff < 0)
			while (y >= game->dir_y)
			{
				x = round(slope * (y - start_y) + start_x);
				yx.x = (int32_t)x;
				yx.y = (int32_t)y;
				// printf("%s %d            x %d\n", __FILE__, __LINE__, yx.x);
				// printf("%s %d            y %d\n\n", __FILE__, __LINE__, yx.y);
				pixset_yx_height_width(game->minimap, get_rgba(r, g, b, a), yx, height_width);
				y--;
			}
	}
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
		// printf("%s %d y %u x %u\n", __FILE__, __LINE__, y, x) ;
		// printf("%s %d xy.y %u xy.x %u\n", __FILE__, __LINE__, xy.y, xy.x) ;
		// printf("%s %d xy.y + y %u xy.x + x %u\n", __FILE__, __LINE__, xy.y + y, xy.x + x) ;
		while (x < height_width.width)
		{
			// printf("%s %d xy.y %f xy.x %f\n", __FILE__, __LINE__, xy.y, xy.x) ;
			// printf("%s %d xy.y %d xy.x %d\n", __FILE__, __LINE__, xy.y, xy.x) ;
			// printf("%s %d xy.y + y %u xy.x + x %u\n", __FILE__, __LINE__, xy.y + y, xy.x + x) ;
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

	// height_width.height = MINI_UNITS_PER_TILE;
	// height_width.width = MINI_UNITS_PER_TILE;
	height_width.height = MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	height_width.width = MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
	y = 0;
	x = 0;
	// game->minimap = mlx_new_image(game->mlx, game->map.max_x * MINI_UNITS_PER_TILE,
	// 	game->map.max_y * MINI_UNITS_PER_TILE);
	game->minimap = mlx_new_image(game->mlx,
						game->map.max_x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR,
						game->map.max_y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR);

	while (game->map.tiles[y] != NULL)
	{
		while (game->map.tiles[y][x] != 0)
		{
			// yx.y = y * MINI_UNITS_PER_TILE;
			// yx.x = x * MINI_UNITS_PER_TILE;
			yx.y = y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
			yx.x = x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR;
			if (game->map.tiles[y][x] != '0' && game->map.tiles[y][x] != ' ')
			{
				pixset_yx_height_width(game->minimap, get_rgba(0, 77, 77, 255),
					yx, height_width);
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
	// 	ft_error("Error\nImage didn't arrive at window", 1, game);
	// }
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
	pixset_yx_height_width(game->miniplayer, get_rgba(0, 200, 0, 255), yx,
		height_width);
	// pixset_yx_height_width(game->miniplayer, 0, yx, height_width);
	if (mlx_image_to_window(game->mlx, game->miniplayer,
		game->player.pos.x * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR,
		game->player.pos.y * MINI_UNITS_PER_TILE * MINI_RESIZE_FACTOR) < 0)
	{
		ft_error("Error\nImage didn't arrive at window", 1, game);
	}
	printf("%s %d            \n\n", __FILE__, __LINE__);
	if (game->miniplayer)
	{
		printf("%s %d            \n\n", __FILE__, __LINE__);
		game->miniplayer->instances->x = game->player.pos.x * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
		game->miniplayer->instances->y = game->player.pos.y * MINI_RESIZE_FACTOR * MINI_UNITS_PER_TILE;
		printf("%s %d            \n\n", __FILE__, __LINE__);
		// mlx_resize_image(game->miniplayer, game->miniplayer->width * MINI_RESIZE_FACTOR,
		// 	game->miniplayer->height * MINI_RESIZE_FACTOR);
	}
	printf("%s %d            \n\n", __FILE__, __LINE__);

	// game->miniplayer->instances->x = game->player.pos.x * MINI_UNITS_PER_TILE;
	// game->miniplayer->instances->y = game->player.pos.y * MINI_UNITS_PER_TILE;
	// printf("%s %d mini x %d  mini y %d\n", __FILE__, __LINE__, game->miniplayer->instances->x, game->miniplayer->instances->y);
	// printf("%s %d mini width %d mini heigth %d\n", __FILE__, __LINE__, game->miniplayer->width, game->miniplayer->height);
}