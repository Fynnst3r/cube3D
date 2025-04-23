/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:09:10 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 19:10:26 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '	' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

void	ft_skip_spaces(const char *str, size_t *index)
{
	while (str[(*index)] && ft_isspace(str[(*index)]))
		(*index)++;
}

// READS ENTIRE FILE no checks at all
// and it deletes all empty lines because of ft_split
char	**read_scenefile(char *av)
{
	int		fd;
	char	*map_lines;
	char	*buff;
	char	*tmp;
	char	**res;

	map_lines = ft_strdup("");
	fd = open(av, O_RDONLY);
	while (1)
	{
		tmp = map_lines;
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		map_lines = f_strjoin(tmp, buff);
		ft_free(tmp);
		tmp = NULL;
		ft_free(buff);
		buff = NULL;
	}
	res = ft_split(map_lines, '\n');
	ft_free(map_lines);
	map_lines = NULL;
	close(fd);
	return (res);
}

bool	check_for_errors(const char *scene_line, size_t l)
{
	ft_skip_spaces(scene_line, &l);
	while (scene_line[l] && (ft_isdigit(scene_line[l])
			|| scene_line[l] == ',' || ft_isspace(scene_line[l])))
		l++;
	if (scene_line[l] != 0)
		return (printf("Error\nNon digit in color\n"), true);
	return (false);
}

bool	recieved_all_elements(t_game *game)
{
	if (game->textures.ea_tex && game->textures.no_tex
		&& game->textures.we_tex && game->textures.so_tex
		&& game->map.recieved_color1 && game->map.recieved_color2)
		return (true);
	return (false);
}
