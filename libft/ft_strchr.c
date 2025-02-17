/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:19:14 by fforster          #+#    #+#             */
/*   Updated: 2024/04/04 19:07:48 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
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

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	printf("mine %s\nofic %s", ft_strchr("test", '\0'), strchr("test", '\0'));
// }