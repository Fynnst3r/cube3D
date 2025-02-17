/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:31:15 by fforster          #+#    #+#             */
/*   Updated: 2024/07/30 14:39:27 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*f_calloc(size_t a, size_t b);
char	*f_strjoin(char *s1, char *s2);
size_t	f_strlen(const char *s);
char	*f_strdup(const char *s1);
char	*f_strchr(const char *s, int c);
char	*f_substr(char const *s, unsigned int start, size_t len);

#endif