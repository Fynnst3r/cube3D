/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:43:46 by fforster          #+#    #+#             */
/*   Updated: 2024/04/05 15:43:22 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_count_digit(int n)
{
	int	cnt_digit;

	cnt_digit = 0;
	if (n == 0)
		cnt_digit = 1;
	while (n > 0)
	{
		n = n / 10;
		cnt_digit++;
	}
	return (cnt_digit);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		cnt_digit;
	int		min_flag;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	min_flag = 0;
	if (n < 0)
	{
		n *= -1;
		min_flag = 1;
	}
	cnt_digit = f_count_digit(n);
	res = (char *)ft_calloc(sizeof(char), (cnt_digit + 1 + min_flag));
	if (!res)
		return (0);
	if (min_flag == 1)
		res[0] = '-';
	while (cnt_digit != 0)
	{
		res[cnt_digit-- - 1 + min_flag] = n % 10 + 48;
		n /= 10;
	}
	return (res);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s", ft_itoa(-2147483647));
// }