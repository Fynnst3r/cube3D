/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsloniow <nsloniow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:44:39 by fforster          #+#    #+#             */
/*   Updated: 2025/02/17 15:18:28 by nsloniow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# ifndef ANSI_RESET
#  define ANSI_RESET "\x1b[0m"
# endif // ANSI_RESET

# ifndef ANSI_BLACK
#  define ANSI_BLACK "\x1b[30m"
# endif // ANSI_BLACK

# ifndef ANSI_RED
#  define ANSI_RED "\x1b[31m"
# endif // ANSI_RED

# ifndef ANSI_GREEN
#  define ANSI_GREEN "\x1b[32m"
# endif // ANSI_GREEN

# ifndef ANSI_YELLOW
#  define ANSI_YELLOW "\x1b[33m"
# endif // ANSI_YELLOW

# ifndef ANSI_BLUE
#  define ANSI_BLUE "\x1b[34m"
# endif // ANSI_BLUE

# ifndef ANSI_MAGENTA
#  define ANSI_MAGENTA "\x1b[35m"
# endif // ANSI_MAGENTA

# ifndef ANSI_CYAN
#  define ANSI_CYAN "\x1b[36m"
# endif // ANSI_CYAN

# ifndef ANSI_WHITE
#  define ANSI_WHITE "\x1b[37m"
# endif // ANSI_WHITE

// Bright Colors
# ifndef ANSI_BRIGHT_BLACK
#  define ANSI_BRIGHT_BLACK "\x1b[90m"
# endif // ANSI_BRIGHT_BLACK

# ifndef ANSI_BRIGHT_RED
#  define ANSI_BRIGHT_RED "\x1b[91m"
# endif // ANSI_BRIGHT_RED

# ifndef ANSI_BRIGHT_GREEN
#  define ANSI_BRIGHT_GREEN "\x1b[92m"
# endif // ANSI_BRIGHT_GREEN

# ifndef ANSI_BRIGHT_YELLOW
#  define ANSI_BRIGHT_YELLOW "\x1b[93m"
# endif // ANSI_BRIGHT_YELLOW

# ifndef ANSI_BRIGHT_BLUE
#  define ANSI_BRIGHT_BLUE "\x1b[94m"
# endif // ANSI_BRIGHT_BLUE

# ifndef ANSI_BRIGHT_MAGENTA
#  define ANSI_BRIGHT_MAGENTA "\x1b[95m"
# endif // ANSI_BRIGHT_MAGENTA

# ifndef ANSI_BRIGHT_CYAN
#  define ANSI_BRIGHT_CYAN "\x1b[96m"
# endif // ANSI_BRIGHT_CYAN

# ifndef ANSI_BRIGHT_WHITE
#  define ANSI_BRIGHT_WHITE "\x1b[97m"
# endif // ANSI_BRIGHT_WHITE

// Background Colors
# ifndef ANSI_BG_BLACK
#  define ANSI_BG_BLACK "\x1b[40m"
# endif // ANSI_BG_BLACK

# ifndef ANSI_BG_RED
#  define ANSI_BG_RED "\x1b[41m"
# endif // ANSI_BG_RED

# ifndef ANSI_BG_GREEN
#  define ANSI_BG_GREEN "\x1b[42m"
# endif // ANSI_BG_GREEN

# ifndef ANSI_BG_YELLOW
#  define ANSI_BG_YELLOW "\x1b[43m"
# endif // ANSI_BG_YELLOW

# ifndef ANSI_BG_BLUE
#  define ANSI_BG_BLUE "\x1b[44m"
# endif // ANSI_BG_BLUE

# ifndef ANSI_BG_MAGENTA
#  define ANSI_BG_MAGENTA "\x1b[45m"
# endif // ANSI_BG_MAGENTA

# ifndef ANSI_BG_CYAN
#  define ANSI_BG_CYAN "\x1b[46m"
# endif // ANSI_BG_CYAN

# ifndef ANSI_BG_WHITE
#  define ANSI_BG_WHITE "\x1b[47m"
# endif // ANSI_BG_WHITE

// Bright Background Colors
# ifndef ANSI_BG_BRIGHT_BLACK
#  define ANSI_BG_BRIGHT_BLACK "\x1b[100m"
# endif // ANSI_BG_BRIGHT_BLACK

# ifndef ANSI_BG_BRIGHT_RED
#  define ANSI_BG_BRIGHT_RED "\x1b[101m"
# endif // ANSI_BG_BRIGHT_RED

# ifndef ANSI_BG_BRIGHT_GREEN
#  define ANSI_BG_BRIGHT_GREEN "\x1b[102m"
# endif // ANSI_BG_BRIGHT_GREEN

# ifndef ANSI_BG_BRIGHT_YELLOW
#  define ANSI_BG_BRIGHT_YELLOW "\x1b[103m"
# endif // ANSI_BG_BRIGHT_YELLOW

# ifndef ANSI_BG_BRIGHT_BLUE
#  define ANSI_BG_BRIGHT_BLUE "\x1b[104m"
# endif // ANSI_BG_BRIGHT_BLUE

# ifndef ANSI_BG_BRIGHT_MAGENTA
#  define ANSI_BG_BRIGHT_MAGENTA "\x1b[105m"
# endif // ANSI_BG_BRIGHT_MAGENTA

# ifndef ANSI_BG_BRIGHT_CYAN
#  define ANSI_BG_BRIGHT_CYAN "\x1b[106m"
# endif // ANSI_BG_BRIGHT_CYAN

# ifndef ANSI_BG_BRIGHT_WHITE
#  define ANSI_BG_BRIGHT_WHITE "\x1b[107m"
# endif // ANSI_BG_BRIGHT_WHITE

// Text Styles
# ifndef ANSI_BOLD
#  define ANSI_BOLD "\x1b[1m"
# endif // ANSI_BOLD

# ifndef ANSI_UNDERLINE
#  define ANSI_UNDERLINE "\x1b[4m"
# endif // ANSI_UNDERLINE

# ifndef ANSI_ITALIC
#  define ANSI_ITALIC "\x1b[3m"
# endif // ANSI_ITALIC

#endif // ANSI_COLORS_H
