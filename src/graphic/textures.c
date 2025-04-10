/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:13:44 by fforster          #+#    #+#             */
/*   Updated: 2025/04/10 15:43:03 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	*create_color_array(t_game *g, mlx_texture_t *tex)
{
	int		*ret;
	size_t	i;
	size_t	x;

	ret = ft_malloc(sizeof(int) * (tex->height * tex->width));
	if (!ret)
		ft_error("color array did not allocate", 42, g);
	x = 0;
	i = 0;
	while (x < tex->width * tex->height)
	{
		ret[i] = get_rgba(tex->pixels[x], tex->pixels[x + 1],
				tex->pixels[x + 2], tex->pixels[x + 3]);
		x += 4;
		i++;
	}
	return (ret);
}

// this function is to test how textures work in mlx
// put pixel works even without specifying the height
// one pixels color consists of four integers in the array image/texture.pixels
// void	draw_half_tex(t_game *g)
// {
// 	size_t	x = 0;
// 	size_t	y = 0;
// 	size_t	i = 0;

// 	// printf("height %i\n witdhh %i\n", g->img->height, g->img->width);
// 	while (y < g->img->height)
// 	{
// 		while (x < g->img->width)
// 		{
// 			mlx_put_pixel(g->img, x, y, get_rgba(g->textures.no_tex->pixels[i],
// 					g->textures.no_tex->pixels[i + 1],
// 					g->textures.no_tex->pixels[i + 2],
// 					g->textures.no_tex->pixels[i + 3]));
// 			x++;
// 			i += 4;
// 		}
// 		x = 0;
// 		y++;
// 	}
// 	// mlx_put_pixel(g->img, x, y, g->wall->pixels[y]);
// 	mlx_image_to_window(g->mlx, g->img, 25, 25);
	// size_t	x = 0;
	// size_t	y = 0;
	// size_t	i = 0;

	// g->textures.wallcolors = create_color_array(g, g->textures.walltex);
	// while (y < g->img->height)
	// {
	// 	while (x < g->img->width)
	// 	{
	// 		mlx_put_pixel(g->img, x, y, g->textures.wallcolors[i]);
	// 		x++;
	// 		i++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	// mlx_put_pixel(g->img, x, y, g->wall->pixels[y]);
	// mlx_image_to_window(g->mlx, g->img, 25, 25);
}
