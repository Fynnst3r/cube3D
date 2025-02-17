/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:26:10 by fforster          #+#    #+#             */
/*   Updated: 2024/10/20 19:19:35 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)ft_malloc(len + 1 * sizeof(const char));
	if (!sub)
		return (0);
	if (start >= ft_strlen(s))
	{
		sub[0] = 0;
		return (sub);
	}
	while (len > 0)
	{
		sub[i] = s[start];
		i++;
		start++;
		len--;
	}
	sub[i] = 0;
	return (sub);
}
// #include<stdio.h>
// int main()
// {
// 	char const *s = "1243";
// 	unsigned int start = 2;
// 	size_t len = 3;
// 	printf("%s", ft_substr(s, start, len));
// }