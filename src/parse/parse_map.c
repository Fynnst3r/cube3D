/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:40:53 by fforster          #+#    #+#             */
/*   Updated: 2025/03/31 17:31:59 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// tiles needs to be seperated from other scene variables like NS or F and C
void	map_len(t_map *map)
{
	size_t	y;

	y = -1;
	while (map->tiles[++y])
		if (ft_strlen(map->tiles[y]) > map->max_y)
			map->max_x = ft_strlen(map->tiles[y]);
	map->max_y = y;
	printf("map y = %zu/map x = %zu\n", map->max_y, map->max_x);
}

static int	find_player(t_map *map, t_player *player)
{
	size_t	x;
	size_t	y;
	int		found;

	x = 0;
	y = 0;
	found = 0;
	while (map->tiles[y])
	{
		while (map->tiles[y][x])
		{
			if (map->tiles[y][x] == 'N' || map->tiles[y][x] == 'E'
				|| map->tiles[y][x] == 'S' || map->tiles[y][x] == 'W')
			{
				player->pos.x = x + 0.5;
				player->pos.y = y + 0.5;
			printf(ANSI_GREEN"player->pos.x = %f\nplayer->pos.y = %f\n"ANSI_RESET, player->pos.x, player->pos.y);
				found++;
				player->looking = map->tiles[y][x];
				map->tiles[y][x] = '0';
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (found);
}

void	parse_map(t_map *map, t_player *player, t_textures *tex)
{
	map->tiles = read_scenefile("maps/simple.cub");
	map_len(map);
	if (find_player(map, player) != 1)
		parse_error(map, tex, "Too many or no players!", 3);
}
