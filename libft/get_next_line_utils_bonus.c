/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:43:04 by fforster          #+#    #+#             */
/*   Updated: 2024/10/20 19:19:45 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	f_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*f_strjoin(char *s1, char *s2)
{
	char	*jnd;
	size_t	i;
	size_t	l;

	jnd = (char *)ft_malloc(sizeof(*s1) * (f_strlen(s1) + f_strlen(s2) + 1));
	if (jnd == 0)
		return (0);
	i = 0;
	l = 0;
	while (s1[l])
	{
		jnd[i] = s1[l];
		i++;
		l++;
	}
	l = 0;
	while (s2[l])
	{
		jnd[i] = s2[l];
		i++;
		l++;
	}
	jnd[i] = 0;
	return (jnd);
}

char	*f_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *)ft_malloc(sizeof(*s1) * f_strlen(s1) + 1);
	if (dup == 0)
		return (0);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*f_strchr(const char *s, int c)
{
	unsigned char	*cs;
	unsigned char	cc;
	size_t			i;

	cs = (unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (cs[i] != 0)
	{
		if (cs[i] == cc)
			return ((char *)&cs[i]);
		i++;
	}
	if (cc == 0)
		return ((char *)&cs[i]);
	return (NULL);
}

char	*f_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (start > f_strlen(s))
		return (f_strdup(""));
	if (len > f_strlen(s) - start)
		len = f_strlen(s) - start;
	sub = (char *)ft_malloc(len + 1 * sizeof(const char));
	if (!sub)
		return (0);
	if (start >= f_strlen(s))
	{
		sub[0] = 0;
		return (sub);
	}
	while (len > 0)
	{
		sub[i] = s[start];
		i++;
		start++;
		len--;
	}
	sub[i] = 0;
	return (sub);
}
