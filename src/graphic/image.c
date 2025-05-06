/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:36:41 by nsloniow          #+#    #+#             */
/*   Updated: 2025/05/06 15:31:58 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

unsigned int	get_rgba(int r, int g, int b, int a);
void			pixset_yx_height_width(mlx_image_t *img, int colour,
					t_cords_int32 xy, t_height_width height_width);

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	pixset_yx_height_width(mlx_image_t *img, int colour, t_cords_int32 xy,
	t_height_width height_width)
{
	u_int32_t	x;
	u_int32_t	y;

	x = 0;
	y = 0;
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
