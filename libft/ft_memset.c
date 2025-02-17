/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:09:45 by fforster          #+#    #+#             */
/*   Updated: 2024/04/04 19:12:23 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*sb;
	size_t	i;

	c = (unsigned char)c;
	sb = (char *)b;
	i = 0;
	while (len != 0)
	{
		sb[i] = c;
		i++;
		len--;
	}
	return (sb);
}
// #include<stdio.h>
// int main()
// {
// 	char b[] = "endme";
// 	printf("%s", ft_memset(b, 48, 5));
// }