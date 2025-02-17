/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:07:16 by fforster          #+#    #+#             */
/*   Updated: 2024/10/08 15:09:06 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_puthex(unsigned int n, bool x, bool counted, size_t *ret)
{
	const char		*hexdex_low;
	const char		*hexdex_up;
	unsigned int	save;

	hexdex_low = "0123456789abcdef";
	hexdex_up = "0123456789ABCDEF";
	save = n;
	if (n == 0)
		(*ret)++;
	if (counted == false)
	{
		while (save != 0)
		{
			save /= 16;
			(*ret)++;
		}
		counted = true;
	}
	if (n >= 16)
		f_puthex(n / 16, x, counted, ret);
	if (x == true)
		write(1, &hexdex_low[n % 16], 1);
	else if (x == false)
		write(1, &hexdex_up[n % 16], 1);
}

void	f_putpoint(unsigned long n, bool counted, size_t *ret)
{
	const char		*hexdex;

	hexdex = "0123456789abcdef";
	if (counted == false)
	{
		write(1, "0x", 2);
		(*ret) += 2;
		counted = true;
	}
	if (n >= 16)
		f_putpoint(n / 16, counted, ret);
	write(1, &hexdex[n % 16], 1);
	(*ret)++;
}

void	f_check_specifier(const char *s, va_list args, size_t i, size_t *pret)
{
	if (s[i] == 'c')
		f_putchar(va_arg(args, int), pret);
	else if (s[i] == 's')
		f_putstr(va_arg(args, char *), pret);
	else if (s[i] == 'p')
		f_putpoint(va_arg(args, unsigned long), false, pret);
	else if (s[i] == 'd')
		f_putnbr(va_arg(args, int), pret);
	else if (s[i] == 'i')
		f_putnbr(va_arg(args, int), pret);
	else if (s[i] == 'u')
		f_putnbr_unsig(va_arg(args, unsigned int), pret);
	else if (s[i] == 'x')
		f_puthex(va_arg(args, unsigned int), true, false, pret);
	else if (s[i] == 'X')
		f_puthex(va_arg(args, unsigned int), false, false, pret);
	else if (s[i] == '%')
		f_putchar('%', pret);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	size_t	i;
	size_t	ret;
	size_t	*pret;

	va_start(args, s);
	i = 0;
	ret = 0;
	pret = &ret;
	while (s[i])
	{
		if (s[i] != '%')
			f_putchar(s[i], pret);
		else if (s[i] == '%')
		{
			i++;
			f_check_specifier(s, args, i, pret);
		}
		i++;
	}
	va_end(args);
	return (ret);
}

// #include<stdio.h>
// int main()
// {
// 	char			c = 'C';
// 	char			*str = NULL;
// 	void			*p = &c;
// 	int				i = -235;
// 	int				d = 529846;
// 	unsigned int	u = 4294967295;
// 	unsigned int	x = 0;
// 	printf("c		%c\n", c);
// 	ft_printf("c		%c\n\n", c);
// 	printf("str		%s\n", str);
// 	ft_printf("str		%s\n\n", str);
// 	printf("%d ", printf("p		%p\n", p));
// 	printf("%d ", ft_printf("p		%p\n\n", p));
// 	printf("d		%d\n", d);
// 	ft_printf("d		%d\n\n", d);
// 	printf("i		%i\n", i);
// 	ft_printf("i		%i\n\n", i);
// 	printf("u		%u\n", u);
// 	ft_printf("u		%u\n\n", u);
// 	printf("%d ", printf("x		%x\n", x));
// 	printf("%d ", ft_printf("x		%x\n\n", x));
// 	printf("X		%X\n", x);
// 	ft_printf("X		%X\n\n", x);
// }