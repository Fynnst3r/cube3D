/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:20:36 by fforster          #+#    #+#             */
/*   Updated: 2024/03/20 16:16:49 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char			*cs1;
	unsigned char			*cs2;

	if (!n)
		return (0);
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (n - 1 > 0)
	{
		if (*cs1 != *cs2)
			return (*cs1 - *cs2);
		cs1++;
		cs2++;
		n--;
	}
	return (*cs1 - *cs2);
}
// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char s1[] = {0, 0, 127, 0};
// 	char s2[] = {-128, 0, 127, 0};
// 	size_t n = 1;
// 	printf("mine%d\nofic%d", ft_memcmp(s1, s2, n), memcmp(s1, s2, n));	
// }