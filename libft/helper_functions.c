/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:12:35 by fforster          #+#    #+#             */
/*   Updated: 2024/10/20 20:10:28 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_putchar(char c, size_t *ret)
{
	write(1, &c, 1);
	(*ret)++;
}

void	f_putstr(char *s, size_t *ret)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		(*ret) += 6;
		return ;
	}
	while (s[i] != 0)
	{
		write(1, &s[i], 1);
		i++;
		(*ret)++;
	}
}

void	f_putnbr(int n, size_t *ret)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		(*ret)++;
	}
	if (n == -2147483648)
	{
		write(1, "2147483648", 10);
		(*ret) += 10;
	}
	if (n >= 0 && n <= 9)
	{
		c = n + '0';
		write(1, &c, 1);
		(*ret)++;
	}
	if (n > 9)
	{
		f_putnbr(n / 10, ret);
		f_putnbr(n % 10, ret);
	}
}

void	f_putnbr_unsig(unsigned int n, size_t *ret)
{
	char	c;

	if (n <= 9)
	{
		c = n + '0';
		write(1, &c, 1);
		(*ret)++;
	}
	if (n > 9)
	{
		f_putnbr_unsig(n / 10, ret);
		f_putnbr_unsig(n % 10, ret);
	}
}
