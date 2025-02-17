/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:36:09 by fforster          #+#    #+#             */
/*   Updated: 2024/10/20 19:19:13 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *)ft_malloc(sizeof(*s1) * ft_strlen(s1) + 1);
	if (dup == 0)
		return (0);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char s[] = "AAAAAAAAAAAA";
// 	printf("mine %s END\nofic %s", ft_strdup(s), strdup(s));
// }