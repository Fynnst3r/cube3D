/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:43:30 by fforster          #+#    #+#             */
/*   Updated: 2025/04/01 18:44:06 by fforster         ###   ########.fr       */
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

char	*get_tex_path(const char *scene_line, size_t l)
{
	size_t	start;
	char	*sub;
	char	*trim;

	if (!ft_isspace(scene_line[l]))
	{
		printf("Error\nTexture Path needs to be seperated with a space!\n");
		return (NULL);
	}
	while (scene_line[l] && ft_isspace(scene_line[l]))
		l++;
	start = l;
	while (scene_line[l] && !ft_isspace(scene_line[l]))
		l++;
	sub = ft_substr(scene_line, start, l);
	trim = ft_strtrim(sub, " \t\f\r\v\n");
	ft_free(sub);
	return (trim);
}

int	check_tex_dir(char dir_identifer[3])
{
	if (!ft_strncmp(dir_identifer, "NO", 3))
		return (1);
	if (!ft_strncmp(dir_identifer, "SO", 3))
		return (2);
	if (!ft_strncmp(dir_identifer, "WE", 3))
		return (3);
	if (!ft_strncmp(dir_identifer, "EA", 3))
		return (4);
	return (0);
}

void	load_texture(t_textures *t, char *path, int dir)
{
	mlx_texture_t	*tmp;

	if (!path)
		parse_error(NULL, t, "Could not find path of texture", 4);
	tmp = mlx_load_png(path);
	ft_free(path);
	path = NULL;
	if (!tmp)
		parse_error(NULL, t, "Could not create a wall texture", 5);
	if (dir == NO)
		t->no_tex = tmp;
	if (dir == SO)
		t->so_tex = tmp;
	if (dir == WE)
		t->we_tex = tmp;
	if (dir == EA)
		t->ea_tex = tmp;
}

// void	get_textures(t_game *game, char **raw_scene)
// {
// 	size_t	i;
// 	size_t	l;
// 	char	dir_element[3];
// 	char	*cur_path;

// 	i = 0;
// 	while (raw_scene[i] && i != 4)
// 	{
// 		l = 0;
// 		while (raw_scene[i][l] && ft_isspace(raw_scene[i][l]))
// 			l++;
// 		dir_element[0] = raw_scene[i][l];
// 		dir_element[1] = raw_scene[i][l + 1];
// 		dir_element[2] = 0;
// 		cur_path = get_tex_path(raw_scene[i], l + 3);
// 		printf("cur path '%s'\n", cur_path);
// 		load_texture(&game->textures, cur_path, check_tex_dir(dir_element));
// 		i++;
// 	}
// }

int	check_element(const char *element)
{
	if (!ft_strncmp(element, "NO", 3))
		return (NO);
	if (!ft_strncmp(element, "SO", 3))
		return (SO);
	if (!ft_strncmp(element, "WE", 3))
		return (WE);
	if (!ft_strncmp(element, "EA", 3))
		return (EA);
	if (element[0] == 'F' && ft_isspace(element[1]))
		return (FLOOR);
	if (element[0] == 'C' && ft_isspace(element[1]))
		return (CEILING);
	return (UNIDENTIFIED);
}

void	get_color(t_game *game, const char *scene_line, int element, size_t l)
{
	int	r;
	int	g;
	int	b;

	if (element == UNIDENTIFIED)
		parse_error(NULL, &game->textures, "Unidentified element in scene", 6);
	ft_skip_spaces(scene_line, &l);
printf("scene_line %s\n", scene_line);
	if (!ft_isdigit(scene_line[l]))
		parse_error(NULL, &game->textures, "Non digit in color", 7);
	r = ft_atoi(&scene_line[l]);
printf(ANSI_RED"r = %i\n"ANSI_RESET, r);
printf("1L = %zu\n", l);
	while (scene_line[l] && scene_line[l] != ',')
		l++;
printf("2L = %zu\n", l);
	l++;
	ft_skip_spaces(scene_line, &l);
	g = ft_atoi(&scene_line[l]);
printf(ANSI_GREEN"g = %i\n"ANSI_RESET, g);
printf("3L = %zu\n", l);
	while (scene_line[l] && scene_line[l] != ',')
		l++;
printf("4L = %zu\n", l);
	l++;
	ft_skip_spaces(scene_line, &l);
	b = ft_atoi(&scene_line[l]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		parse_error(NULL, &game->textures, "Color value out of range", 8);
	if (element == FLOOR)
		game->map.floor_color = get_rgba(r, g, b, 255);
	else
		game->map.ceiling_color = get_rgba(r, g, b, 255);
printf(ANSI_BLUE"b = %i\n"ANSI_RESET, b);
}
// l starts behind element, jump to first non space, continue digit until comma,
// if false input like out of range or non digit exit(), 

void	scan_elements(t_game *game, char **raw_scene)
{
	size_t	i;
	size_t	l;
	char	element[3];
	char	*cur_path;

	i = 0;
	while (raw_scene[i] && i != 6)
	{
		l = 0;
		while (raw_scene[i][l] && ft_isspace(raw_scene[i][l]))
			l++;
		element[0] = raw_scene[i][l];
		element[1] = raw_scene[i][l + 1];
		element[2] = 0;
		if (check_element(element) < FLOOR)
		{
			cur_path = get_tex_path(raw_scene[i], l + 2);
			printf("cur path '%s'\n", cur_path);
			load_texture(&game->textures, cur_path, check_element(element));
		}
		else
			get_color(game, raw_scene[i], check_element(element), l + 1);
		i++;
	}
}

void	parse_scene(t_game *game, int ac, char **av)
{
	char	**raw_scene;

	raw_scene = NULL;
	if (ac != 2)
		parse_error(NULL, NULL, "No map or too many specified (e.g maps/[name].cub)", 2);
	raw_scene = read_scenefile(av[1]);
	if (!raw_scene)
		parse_error(NULL, NULL, "Error\nNo Scene", 3);
	scan_elements(game, raw_scene);
	// get_textures(game, raw_scene);
}
// textures and colors can come in any order
// check which element, check if its already set, check value, parse value, continue until all 6 elements are set