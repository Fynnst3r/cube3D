/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:19:11 by fforster          #+#    #+#             */
/*   Updated: 2024/04/04 19:12:14 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*pdst;
	char		*psrc;
	size_t		i;

	pdst = (char *)dst;
	psrc = (char *)src;
	i = 0;
	if (len == 0)
		return (dst);
	if (!dst && !src && len > 0)
		return (dst);
	if (pdst >= psrc)
	{
		while (len-- != 0)
			pdst[len] = psrc[len];
	}
	else
	{
		while (len-- != 0)
		{
			pdst[i] = psrc[i];
			i++;
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {	size_t	l = 7;
// 	char		dst[] = "donotcpy";
// 	const char	src[] = "plsdo";
// 	printf("mine %s\n%s\n", ft_memmove(dst, src, l), dst);
// 	printf("mine %p\n%p\n------------\n", ft_memmove(dst, src, l), dst);
// 	printf("ofic %s\n%s\n", memmove(dst, src, l), dst);
// 	printf("ofic %p\n%p\n", memmove(dst, src, l), dst);
// }