/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:13:44 by fforster          #+#    #+#             */
/*   Updated: 2025/04/18 15:00:41 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int *create_color_array(t_game *g, mlx_texture_t *tex)
{
    int     *ret;
    size_t  pix_cnt;
    size_t  x;
    // size_t  y = 0;

    ret = ft_malloc(sizeof(int) * (tex->height * tex->width));
    if (!ret)
        ft_error("color array did not allocate", 42, g);
    x = 0;
    pix_cnt = 0;
    while (x < tex->width * tex->height * 4)
    // while (y < tex->height)
	// {
		// while (x < tex->width)
        // while (x < (tex->width -1) * 4)
		{
            ret[pix_cnt] = get_rgba(tex->pixels[x], tex->pixels[x + 1],
                    tex->pixels[x + 2], tex->pixels[x + 3]);
            // if (pix_cnt == 5)
            // {
            //     printf("%s %d r %d g %d b %d a %d rgba %d ret pix_cnt %d\n", __FILE__, __LINE__,
            //         tex->pixels[x], tex->pixels[x + 1],
            //         tex->pixels[x + 2], tex->pixels[x + 3],
            //         get_rgba(tex->pixels[x], tex->pixels[x + 1],
            //             tex->pixels[x + 2], tex->pixels[x + 3]), ret[pix_cnt]);
            // }
            // printf("%s %dcreate colour pixel %zu rgba %d\n", __FILE__, __LINE__, pix_cnt, ret[pix_cnt]);
            // mlx_put_pixel(g->img, x, y, g->textures.color_ea[pix_cnt]);
            x += 4;
            pix_cnt++;
        }
    //     x = 0;
    //     y ++;
    // }
    return (ret);
}
void    fill_texture_colors(t_game *game)
{
    size_t  i = 0;
    size_t  x = 0;
    size_t  y = 0;
    // int x = 5;
    game->textures.color_no = create_color_array(game, game->textures.no_tex);
    // printf("%s %d rgba %d\n", __FILE__, __LINE__,
    //     game->textures.color_no[x]);
    game->textures.color_so = create_color_array(game, game->textures.so_tex);
    game->textures.color_we = create_color_array(game, game->textures.we_tex);  
    game->textures.color_ea = create_color_array(game, game->textures.ea_tex);
    while (y < game->textures.ea_tex->height)
	{
		while (x < game->textures.ea_tex->width)
		{            
            // printf("%s %d fill calling create pixel %zu rgba %d\n", __FILE__, __LINE__, i, game->textures.color_ea[i]);
            // mlx_put_pixel(game->img, x, y, game->textures.color_ea[i]);
            x ++;
            i++;
        }
        x = 0;
        y++;
    }
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
// }
