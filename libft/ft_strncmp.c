/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:31:04 by fforster          #+#    #+#             */
/*   Updated: 2024/03/20 17:34:08 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (n - 1 > 0 && *cs1 && *cs2)
	{
		if (*cs1 != *cs2)
			return (*cs1 - *cs2);
		cs1++;
		cs2++;
		n--;
	}
	return (*cs1 - *cs2);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	// const char s1[] = "123456";
// 	// const char s2[] = "234234";
// 	unsigned char s1[10] = "abcdef";
// 	unsigned char s2[10] = "abc\xfdxx";
// 	printf("%d\n%d", strncmp((char *)s1, (char *)s2, 5),
// 		ft_strncmp((char *)s1, (char *)s2, 5));
// }