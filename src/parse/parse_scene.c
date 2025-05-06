/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:43:30 by fforster          #+#    #+#             */
/*   Updated: 2025/04/24 14:41:47 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	which_element(const char *line, size_t *l)
{
	ft_skip_spaces(line, l);
	if (!ft_strncmp(&line[*l], "NO ", 3))
		return (*l += 2, NO);
	if (!ft_strncmp(&line[*l], "SO ", 3))
		return (*l += 2, SO);
	if (!ft_strncmp(&line[*l], "WE ", 3))
		return (*l += 2, WE);
	if (!ft_strncmp(&line[*l], "EA ", 3))
		return (*l += 2, EA);
	if (!ft_strncmp(&line[*l], "WC ", 3))
		return (*l += 2, WC);
	if (line[*l] == 'F' && ft_isspace(line[*l + 1]))
		return (*l += 1, FLOOR);
	if (line[*l] == 'C' && ft_isspace(line[*l + 1]))
		return (*l += 1, CEILING);
	return (UNIDENTIFIED);
}

int	handle_element(t_game *g, char *scene_line,
		int curr_elem, size_t l)
{
	if (!ft_isspace(scene_line[l]))
		return (printf("Error\nNo 'space' after element\n"), 1);
	if (curr_elem == NO || curr_elem == SO
		|| curr_elem == WE || curr_elem == EA || curr_elem == WC)
		if (make_texture(g, scene_line, curr_elem, l))
			return (2);
	if (curr_elem == FLOOR)
	{
		if (make_color(g, scene_line, FLOOR, l))
			return (3);
		g->map.recieved_color1 = true;
	}
	if (curr_elem == CEILING)
	{
		if (make_color(g, scene_line, CEILING, l))
			return (4);
		g->map.recieved_color2 = true;
	}
	return (0);
}

void	scan_elements(t_game *game, char **raw_scene)
{
	size_t	i;
	size_t	l;
	int		current_element;

	i = 0;
	while (raw_scene[i])
	{
		l = 0;
		current_element = which_element(raw_scene[i], &l);
		if (current_element == UNIDENTIFIED)
			break ;
		if (handle_element(game, raw_scene[i], current_element, l))
			parse_error(&game->map, &game->textures, NULL, raw_scene);
		i++;
	}
	game->map.map_scene_start = i;
	ft_free_dp(raw_scene);
	if (!recieved_all_elements(game))
		parse_error(&game->map, &game->textures,
			"Missing a scene element", NULL);
}

void	parse_scene(t_game *game, int ac, char **av)
{
	char	**raw_scene;

	raw_scene = NULL;
	if (ac != 2)
		parse_error(NULL, NULL,
			"No map or too many specified (e.g maps/[name].cub)", NULL);
	raw_scene = read_scenefile(av[1]);
	if (!raw_scene)
		parse_error(NULL, NULL, "Error\nNo Scene", NULL);
	scan_elements(game, raw_scene);
	fill_texture_colors(game);
}
