/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:19:15 by fforster          #+#    #+#             */
/*   Updated: 2024/04/16 20:39:56 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	l;
	size_t	saved;

	i = 0;
	l = 0;
	saved = ft_strlen(src) + dstsize;
	if (dstsize > ft_strlen(dst))
		saved = ft_strlen(src) + ft_strlen(dst);
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while (dst[i] != 0 && (dstsize - 1) > i)
		i++;
	while (src[l] != 0 && (dstsize - 1) > i)
	{
		dst[i] = src[l];
		i++;
		l++;
	}
	if (i != 0)
		dst[i] = 0;
	return (saved);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	size_t DSTSIZE = 10;
// 	char dst[15] = "welovetoAAAAAA";
// 	char src[10] = "kill";
// 	char dst2[15] = "welovetoAAAAAA";
// 	char src2[10] = "kill";
// 	printf("mine %lu\nofic %lu", ft_strlcat(dst, src, DSTSIZE),
// 		strlcat(dst2, src2, DSTSIZE));
// 	printf("\nmine %s\nofic %s", dst, dst2);
// }