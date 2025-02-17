/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:51:16 by fforster          #+#    #+#             */
/*   Updated: 2024/03/20 16:01:30 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	cc;
	unsigned char	*cs;

	if (!n)
		return (0);
	cc = (unsigned char )c;
	cs = (unsigned char *)s;
	while (n)
	{
		if (*cs == cc)
			return (cs);
		cs++;
		n--;
	}
	return (0);
}
// #include<stdio.h>
// #include<string.h>
// int	main()
// {
// 	char	s[] = ":(){ :|: & };:";
// 	int		c = -34;
// 	size_t	n = 13;
// 	printf("mine%p\nofic%p", ft_memchr(s, c, n), memchr(s, c, n));
// }