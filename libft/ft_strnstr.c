/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:46:58 by fforster          #+#    #+#             */
/*   Updated: 2024/04/04 19:00:26 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		l;

	i = 0;
	l = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] != 0)
	{
		while (needle[l] != 0 && len > i + l)
		{
			if (haystack[i + l] == needle[l])
				l++;
			else
				break ;
			if (needle[l] == 0)
				return ((char *)&haystack[i]);
		}
		i++;
		l = 0;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char	AAA[] = "lorem ipsum dolor sit amet";
// 	const char	BBB[] = "ipsumm";
// 	size_t len = 30;
// 	printf("mine %s\nofic %s", ft_strnstr(AAA, BBB, len),
// 		strnstr(AAA, BBB, len));
// 	// ft_strnstr("fake", ((void *)0), 3);
// }