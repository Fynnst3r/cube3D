/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:59:06 by nsloniow          #+#    #+#             */
/*   Updated: 2025/04/08 13:29:58 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_mlx_draw_pixel(uint8_t *pixel, uint32_t color);
void	ft_mlx_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
			uint32_t color);
int		get_rgba(int r, int g, int b, int a);
void	pixset(mlx_image_t *img, int colour);
void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
							t_height_width height_width);

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
