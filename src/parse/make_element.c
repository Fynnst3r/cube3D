/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:06:01 by fforster          #+#    #+#             */
/*   Updated: 2025/04/22 19:18:50 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

int	make_texture(t_game *g, char *scene_line, int curr_element, size_t l)
{
	char	*tex_path;

	tex_path = get_tex_path(scene_line, l);
	if (load_texture(&g->textures, tex_path, curr_element))
		return (1);
	return (0);
}

int	make_color(t_game *game, char *scene_line, int curr_col, size_t l)
{
	int	r;
	int	g;
	int	b;

	if (check_for_errors(scene_line, l))
		return (1);
	r = ft_atoi(&scene_line[l]);
	while (scene_line[l] && scene_line[l] != ',')
		l++;
	l++;
	ft_skip_spaces(scene_line, &l);
	g = ft_atoi(&scene_line[l]);
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
	return (0);
}
