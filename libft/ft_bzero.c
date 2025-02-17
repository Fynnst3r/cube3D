/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:18:34 by fforster          #+#    #+#             */
/*   Updated: 2024/04/03 17:13:17 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*c;

	c = (char *)s;
	while (n--)
		*c++ = 0;
}

// #include <stdio.h>
// int main()
// {
// 	char str[] = "nichnull";
// 	printf("%s\n", str);
// 	ft_bzero(str, 8);
// 	printf("%s", str);
// }