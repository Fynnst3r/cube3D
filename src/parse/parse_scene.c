/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:43:30 by fforster          #+#    #+#             */
/*   Updated: 2025/04/10 17:25:43 by nsloniow         ###   ########.fr       */
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

void	overwrite_texture(mlx_texture_t **old, mlx_texture_t *new)
{
	if (*old)
	{
		mlx_delete_texture(*old);
		*old = new;
	}
	else
		*old = new;
}

int	load_texture(t_textures *t, char *path, int dir)
{
	mlx_texture_t	*tmp;

	if (!path)
		return (printf("Error\nCould not find path of texture\n"), 1);
	tmp = mlx_load_png(path);
	if (!tmp)
		return (printf("Texture %s failed to load!\n", path), 1);
	ft_free(path);
	path = NULL;
	if (!tmp)
		return (printf("Error\nCould not create a wall texture"), 2);
	if (dir == NO)
		overwrite_texture(&t->no_tex, tmp);
	if (dir == SO)
		overwrite_texture(&t->so_tex, tmp);
	if (dir == WE)
		overwrite_texture(&t->we_tex, tmp);
	if (dir == EA)
		overwrite_texture(&t->ea_tex, tmp);
	return (0);
}

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
	if (line[*l] == 'F' && ft_isspace(line[*l + 1]))
		return (*l += 1, FLOOR);
	if (line[*l] == 'C' && ft_isspace(line[*l + 1]))
		return (*l += 1, CEILING);
	return (UNIDENTIFIED);
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

int	make_texture(t_game *g, char *scene_line, int curr_element, size_t l)
{
	char	*tex_path;

	tex_path = get_tex_path(scene_line, l);
// printf("cur path '%s'\n", tex_path);
	if (load_texture(&g->textures, tex_path, curr_element))
		return (1);
	return (0);
}

int	make_color(t_game *game, char *scene_line, int curr_col, size_t l)
{
	int	r;
	int	g;
	int	b;

// printf("scene_line '%s'\n", &scene_line[l]);
	if (check_for_errors(scene_line, l))
		return (1);
	r = ft_atoi(&scene_line[l]);
// printf(ANSI_RED"r = %i\n"ANSI_RESET, r);
	while (scene_line[l] && scene_line[l] != ',')
		l++;
	l++;
	ft_skip_spaces(scene_line, &l);
	g = ft_atoi(&scene_line[l]);
// printf(ANSI_GREEN"g = %i\n"ANSI_RESET, g);
	while (scene_line[l] && scene_line[l] != ',')
		l++;
	l++;
	ft_skip_spaces(scene_line, &l);
	b = ft_atoi(&scene_line[l]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (printf("Error\nColor value out of range\n"), 2);
	if (curr_col == FLOOR)
		game->map.floor_color = get_rgba(r, g, b, 255);
	else
		game->map.ceiling_color = get_rgba(r, g, b, 255);
// printf(ANSI_BLUE"b = %i\n"ANSI_RESET, b);
	return (0);
}

int	handle_element(t_game *g, char *scene_line,
		int curr_elem, size_t l)
{
	if (!ft_isspace(scene_line[l]))
		return (printf("Error\nNo 'space' after element\n"), 1);
	if (curr_elem == NO || curr_elem == SO
		|| curr_elem == WE || curr_elem == EA)
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

bool	recieved_all_elements(t_game *game)
{
	if (game->textures.ea_tex && game->textures.no_tex
		&& game->textures.we_tex && game->textures.so_tex
		&& game->map.recieved_color1 && game->map.recieved_color2)
		return (true);
	return (false);
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
		// printf("scan[%zu]: '%s'\n", i, raw_scene[i]);
		current_element = which_element(raw_scene[i], &l);
		// printf("curr_elem %i\n", current_element);
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
printf(ANSI_MAGENTA"START %zu\n"ANSI_RESET, game->map.map_scene_start);
}
