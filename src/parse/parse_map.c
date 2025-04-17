/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:40:53 by fforster          #+#    #+#             */
/*   Updated: 2025/04/17 14:38:14 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


int	map_len(t_map *map)
{
	size_t	y;
	size_t	x;

	y = -1;
	while (map->tiles[++y])
	{
		x = -1;
		while (map->tiles[y][++x])
			if (map->tiles[y][x] != '1' && map->tiles[y][x] != '0'
				&& map->tiles[y][x] != 'N' && map->tiles[y][x] != 'E'
				&& map->tiles[y][x] != 'S' && map->tiles[y][x] != 'W'
				&& map->tiles[y][x] != ' ' && map->tiles[y][x] != 'D')
				return (1);
		if (ft_strlen(map->tiles[y]) > map->max_x)
			map->max_x = ft_strlen(map->tiles[y]);
	}
	map->max_y = y;
	printf("map y = %zu/map x = %zu\n", map->max_y, map->max_x);
	return (0);
}

static int	find_player(t_map *map, t_player *player)
{
	size_t	x;
	size_t	y;
	int		found;

	y = 0;
	found = 0;
	while (map->tiles[y])
	{
		x = 0;
		while (map->tiles[y][x])
		{
			if (map->tiles[y][x] == 'N' || map->tiles[y][x] == 'E'
				|| map->tiles[y][x] == 'S' || map->tiles[y][x] == 'W')
			{
				player->pos.x = x + 0.5;
				player->pos.y = y + 0.5;
				map->spawn.x = player->pos.x;
				map->spawn.y = player->pos.y;
			printf(ANSI_GREEN"player->pos.x = %f\nplayer->pos.y = %f\n"ANSI_RESET, player->pos.x, player->pos.y);
				found++;
				player->looking = map->tiles[y][x];
				map->tiles[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (found);
}

char	**crop_scene_to_map(char *path, size_t start)
{
	char	**raw_scene;
	char	**ret;
	size_t	i;
	size_t	k;

	ret = NULL;
	raw_scene = read_scenefile(path);
	i = 0;
	while (raw_scene[i])
		i++;
	ret = ft_calloc(sizeof(char *), i - start + 1);
	if (!ret)
		return (NULL);
	k = -1;
	while (++k != i - start)
		ret[k] = ft_strdup(raw_scene[k + start]);
	k = -1;
	while (raw_scene[++k])
	{
		ft_free(raw_scene[k]);
		raw_scene[k] = NULL;
	}
	return (ft_free(raw_scene), raw_scene = NULL, ret);
}

void	check_walled_map(t_map *map, t_textures *t, size_t y, size_t x)
{
	if (y > map->max_y - 1 || x > ft_strlen(map->copy[y]) - 1)
		parse_error(map, t, "Map is not walled correctly1", NULL);
	if (map->max_x <= x || map->max_y <= y || map->copy[y][x] == '-'
		|| map->copy[y][x] == '1' || map->copy[y][x] == 'D')
		return ;
	if (map->copy[y][x] == '0')
		map->copy[y][x] = '-';
	else if (map->copy[y][x] != '1' || map->copy[y][x] == 0)
		parse_error(map, t, "Map is not walled correctly2", NULL);
	check_walled_map(map, t, y + 1, x);
	check_walled_map(map, t, y - 1, x);
	check_walled_map(map, t, y, x + 1);
	check_walled_map(map, t, y, x - 1);
}

void	parse_map(t_map *map, t_player *player, t_textures *tex, char *path)
{
	map->tiles = crop_scene_to_map(path, map->map_scene_start);
	map->copy = crop_scene_to_map(path, map->map_scene_start);
	if (!map->tiles || !map->copy)
		parse_error(map, tex, "Malloc fail", NULL);
	ft_free(path);
	path = NULL;
	if (map_len(map))
		parse_error(map, tex, "No foreign characters in map please", NULL);
	if (find_player(map, player) != 1)
		parse_error(map, tex, "Too many or no players!", NULL);
	map->copy[(size_t)player->pos.y][(size_t)player->pos.x] = '0';
	check_walled_map(map, tex, (size_t)player->pos.y, (size_t)player->pos.x);
	// size_t y = 0;
	// while (map->copy[y])
	// {
	// 	printf("copy[%zu]:	'%s'\n", y, map->copy[y]);
	// 	y++;
	// }
	// printf("copy[%zu]:	'%s'\n", y, map->copy[y]);
	// printf("map y = %zu/map x = %zu\n", map->max_y, map->max_x);
	// printf("HEAEAEAE\n");
}
