/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:16:01 by fforster          #+#    #+#             */
/*   Updated: 2024/03/13 18:45:20 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (!src && !dst && n > 0)
		return (dst);
	while (n)
	{
		*pdst = *psrc;
		psrc++;
		pdst++;
		n--;
	}
	return (dst);
}
// #include <stdio.h>
// int main(void)
// {
// 	char dst[30];
// 	printf("%s\n%s", ft_memcpy(dst, "asdas", 5), memcpy(dst, "asdas", 5));
// }