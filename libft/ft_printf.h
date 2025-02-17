/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:10:14 by fforster          #+#    #+#             */
/*   Updated: 2024/06/19 19:14:16 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

int		ft_printf(const char *s, ...);
void	f_putchar(char c, size_t *ret);
void	f_putstr(char *s, size_t *ret);
void	f_putnbr(int n, size_t *ret);
void	f_putnbr_unsig(unsigned int n, size_t *ret);
void	f_puthex(unsigned int n, bool x, bool counted, size_t *ret);
void	f_putpoint(unsigned long n, bool counted, size_t *ret);
void	f_check_specifier(const char *s, va_list args, size_t i, size_t *pret);

#endif