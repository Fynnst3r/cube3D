/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:17:37 by fforster          #+#    #+#             */
/*   Updated: 2024/12/17 22:00:13 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	f_free_strs(char **split)
{
	size_t	k;

	k = 0;
	while (split[k] != NULL)
	{
		ft_free(split[k]);
		k++;
	}
	ft_free(split);
}

static size_t	f_count_words(const char *s1, char c)
{
	size_t	i;
	size_t	count;
	int		word_flag;

	i = 0;
	count = 0;
	word_flag = 0;
	while (s1[i])
	{
		if (s1[i] != c && word_flag == 0)
		{
			word_flag = 1;
			count++;
		}
		else if (s1[i] == c)
			word_flag = 0;
		i++;
	}
	return (count);
}

static int	f_fill_str(char const *s, char c, char **split)
{
	size_t	i;
	size_t	l;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != 0)
	{
		while (c == s[i] && s[i] != 0)
			i++;
		l = i;
		while (c != s[l] && s[l] != 0)
			l++;
		if (i < l)
		{
			split[k] = ft_substr(s, i, l - i);
			if (split[k] == 0)
				return (f_free_strs(split), 0);
			k++;
		}
		i = l;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	word_count;

	word_count = f_count_words(s, c);
	split = ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	if (!(f_fill_str(s, c, split)))
		return (NULL);
	return (split);
}

// #include <stdio.h>
// int main()
// {
// 	char *string = "       ";
// 	//char **expected = 
// 	// 	((char*[6]){"split", "this", "for", "me", "!", ((void *)0)});
// 	char **result = ft_split(string, ' ');
// if (result != NULL)
//  for (int i = 0; result[i]; i++)
//  {
// 	printf("%s\n", result[i]);
//  }
// // 	char s[] = " split  splat  sploosh ! ";
// // 	char c = ' ';
// // 	char *end[4] = {"split", "splat", "sploosh", "!"};
// // 	// printf("%s", *ft_split(s, c));
// // 	printf("%s", f_fill_str(s, c));
// }