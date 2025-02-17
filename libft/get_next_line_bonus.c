/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:01:30 by fforster          #+#    #+#             */
/*   Updated: 2024/12/17 22:00:53 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*f_read_line(int fd, char *buffer, char *leftover)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = BUFFER_SIZE;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
			return (ft_free(leftover), NULL);
		buffer[bytes_read] = 0;
		if (!leftover)
			leftover = f_strdup("");
		tmp = leftover;
		leftover = f_strjoin(tmp, buffer);
		ft_free(tmp);
		tmp = NULL;
		if (f_strchr(buffer, '\n'))
			break ;
	}
	return (leftover);
}

static char	*f_cut_str(char *line)
{
	char	*leftover;
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0)
		return (NULL);
	leftover = f_substr(line, i + 1, f_strlen(line) - i);
	if (*leftover == 0)
	{
		ft_free(leftover);
		leftover = NULL;
	}
	line[i + 1] = 0;
	return (leftover);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*leftover[1024];

	if (fd < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		ft_free(leftover[fd]);
		ft_free(buffer);
		return (leftover[fd] = NULL, buffer = NULL, NULL);
	}
	line = f_read_line(fd, buffer, leftover[fd]);
	ft_free(buffer);
	if (!line)
		return (ft_free(leftover[fd]), NULL);
	leftover[fd] = f_cut_str(line);
	return (line);
}
// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		count;
// 	count = 0;
// 	fd = open("example.txt", O_RDONLY);
// 	while (1)
// 	{
// 		next_line = get_next_line(1000);
// 		if (next_line == NULL)
// 			break ;
// 		count++;
// 		printf("[%d]:%s\n", count, next_line);
// 		next_line = NULL;
// 	}
// 	// close(fd);
// 	// open("example.txt", O_RDONLY);
// 	// char buffer[1000];
// 	// while (1)
// 	// {
// 	// 	int val = read(0, buffer, 1000);
// 	// 	buffer[val] = '\n';
// 	// 	buffer[val + 1] = '\0';
// 	// 	printf("%s", buffer);
// 	// }
// 	return (0);
// }
