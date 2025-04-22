/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/04/15 11:10:25 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_mlx_draw_pixel(uint8_t *pixel, uint32_t color);
void	ft_mlx_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
			uint32_t color);
unsigned int		get_rgba(int r, int g, int b, int a);
void	pixset(mlx_image_t *img, int colour);
void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
							t_height_width height_width);
void	draw_half_tex(t_game *g);

// this function is to test how textures work in mlx
// put pixel works even without specifying the height
// one pixels color consists of four integers in the array image/texture.pixels
void	draw_half_tex(t_game *g)
{
	// size_t	x = 0;
	// size_t	y = 0;
	// size_t	i = 0;

	// // printf("height %i\n witdhh %i\n", g->img->height, g->img->width);
	// while (y < g->img->height)
	// {
	// 	while (x < g->img->width)
	// 	{
	// 		mlx_put_pixel(g->img, x, y, get_rgba(g->textures.ea_tex->pixels[i],
	// 				g->textures.ea_tex->pixels[i + 1],
	// 				g->textures.ea_tex->pixels[i + 2],
	// 				g->textures.ea_tex->pixels[i + 3]));
	// 		x++;
	// 		i += 4;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	// // mlx_put_pixel(g->img, x, y, g->wall->pixels[y]);
	// mlx_image_to_window(g->mlx, g->img, 25, 25);
	size_t	x = 0;
	size_t	y = 0;
	size_t	i = 0;


	// g->textures.wallcolors = create_color_array(g, g->textures.walltex);
	while (y < g->img->height)
	{
		while (x < g->img->width)
		{
			printf("%s %d half tex pixel %zu rgba %d\n", __FILE__, __LINE__, i, g->textures.color_ea[i]);
			mlx_put_pixel(g->img, x, y, g->textures.color_ea[i]);
			x++;
			i++;
		}
		x=0;
		y++;
	}
	// mlx_put_pixel(g->img, x, y, g->wall->pixels[y]);
	mlx_image_to_window(g->mlx, g->img, 25, 25);
}

// # define BPP sizeof(int32_t) /* Only support RGBA */
void	ft_mlx_draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	ft_mlx_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
						uint32_t color)
{
	uint8_t	*pixelstart;
	// MLX_NONNULL(image);
	// MLX_ASSERT(x < image->width, "Pixel is out of bounds");
	// MLX_ASSERT(y < image->height, "Pixel is out of bounds");
	// printf("%s %d put px  y %u x %u\n", __FILE__, __LINE__, y, x) ;
	// uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];
	pixelstart = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
	// printf("%s %d put px  y %u x %u\n", __FILE__, __LINE__, y, x) ;
	ft_mlx_draw_pixel(pixelstart, color);
	// printf("%s %d put px  y %u x %u\n", __FILE__, __LINE__, y, x) ;
}

unsigned int	get_rgba(int r, int g, int b, int a)
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
