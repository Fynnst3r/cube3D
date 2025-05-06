/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:13:44 by fforster          #+#    #+#             */
/*   Updated: 2025/05/06 15:56:46 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	*create_color_array(t_game *g, mlx_texture_t *tex)
{
	int		*ret;
	size_t	pix_cnt;
	size_t	x;

	ret = ft_malloc(sizeof(int) * (tex->height * tex->width));
	if (!ret)
		ft_error("color array did not allocate", 42, g);
	x = 0;
	pix_cnt = 0;
	while (x < tex->width * tex->height * 4)
	{
		ret[pix_cnt] = get_rgba(tex->pixels[x], tex->pixels[x + 1],
				tex->pixels[x + 2], tex->pixels[x + 3]);
		x += 4;
		pix_cnt++;
	}
	return (ret);
}

void	fill_texture_colors(t_game *game)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	x = 0;
	y = 0;
	game->textures.color_no = create_color_array(game, game->textures.no_tex);
	game->textures.color_so = create_color_array(game, game->textures.so_tex);
	game->textures.color_we = create_color_array(game, game->textures.we_tex);
	game->textures.color_ea = create_color_array(game, game->textures.ea_tex);
	while (y < game->textures.ea_tex->height)
	{
		while (x < game->textures.ea_tex->width)
		{
			x ++;
			i++;
		}
		x = 0;
		y++;
	}
}
