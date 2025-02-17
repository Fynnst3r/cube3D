/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:34:43 by fforster          #+#    #+#             */
/*   Updated: 2024/10/20 19:18:48 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*m;

	m = ft_malloc(size * count);
	if (!m)
		return (NULL);
	ft_bzero(m, size * count);
	return (m);
}
// #include<stdio.h>
// int main()
// {
// 	char *a = ft_calloc(4, 5);
// 	a = "";
// 	printf("%d", ft_memcmp(ft_calloc(4, 5), calloc(4, 5), 20));
// }