/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:34:36 by fforster          #+#    #+#             */
/*   Updated: 2025/01/03 14:59:15 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		res;
	int		minus;

	res = 0;
	minus = 0;
	while ((*str < 14 && *str > 8) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			minus = -1;
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (minus == -1)
		res *= -1;
	return (res);
}
// #include<stdio.h>
// #include<stdlib.h>
// int main()
// {
// 	const char	str[] = "-984";
// 	printf("%d\n%d", ft_atoi(str), atoi(str));
// }
