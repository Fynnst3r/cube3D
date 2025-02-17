/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:37:31 by fforster          #+#    #+#             */
/*   Updated: 2024/04/04 19:09:21 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	f_strmapi(unsigned int i, char c)
{
	return (c + i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*cs;
	size_t	i;

	cs = (char *)malloc(sizeof(*s) * ft_strlen(s) + 1);
	if (cs == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		cs[i] = f(i, s[i]);
		i++;
	}
	cs[i] = 0;
	return (cs);
}
// #include<stdio.h>
// int main()
// {
// 	printf("%s", ft_strmapi("Grrr", f_strmapi));
// }