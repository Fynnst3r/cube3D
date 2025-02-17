/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:13:21 by fforster          #+#    #+#             */
/*   Updated: 2024/12/19 18:13:49 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*jnd;
	size_t		i;

	jnd = (char *)ft_malloc(sizeof(*s1) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (jnd == 0)
		return (0);
	i = 0;
	while (*s1)
	{
		jnd[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		jnd[i] = *s2;
		i++;
		s2++;
	}
	jnd[i] = 0;
	return (jnd);
}
// #include <stdio.h>
// int main()
// {
// 	printf("%s", ft_strjoin("tripouille", "42"));
// }
