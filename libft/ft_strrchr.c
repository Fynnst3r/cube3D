/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:16:02 by fforster          #+#    #+#             */
/*   Updated: 2024/04/04 19:15:17 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cs;
	char	cc;
	int		i;

	cs = (char *)s;
	cc = c % 256;
	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (cs[i] == cc)
			return (&cs[i]);
		i--;
	}
	if (*s == 0)
		return (0);
	return (0);
}
// #include<stdio.h>
// #include <string.h>
// int main()
// {
// 	char s[] = "";
// 	printf("mine %s\nofic %s", ft_strrchr(s, '\0'), strrchr(s, '\0'));
// }
