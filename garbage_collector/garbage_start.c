/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:28:09 by fforster          #+#    #+#             */
/*   Updated: 2025/02/17 14:49:55 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/garbage_collector.h"

t_trashman	*get_workers(void)
{
	static t_trashman	trashmen = {0};

	return (&trashmen);
}

t_trashman	*init_garbage_collector(void)
{
	t_trashman	*tm;

	tm = get_workers();
	tm->head = NULL;
	tm->tail = NULL;
	tm->worker_num = 0;
	return (tm);
}

// char	*ft_strjoin_at(char *s1, char *s2, size_t start)
// {
// 	size_t	i;
// 	size_t	l;
// 	char	*join;
// 	i = 0;
// 	l = 0;
// 	join = ft_malloc(sizeof(char) * 
	//(ft_strlen(s1) + ft_strlen(s2) + 1 - start));
// 	if (!join)
// 		return (NULL);
// 	while (s1[i] && i != start)
// 	{
// 		join[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[l])
// 	{
// 		join[i] = s2[l];
// 		i++;
// 		l++;
// 	}
// 	join[i] = 0;
// 	return (join);
// }
// int main()
// {
// 	// char	*s1 = "Hello ";
// 	// char	*s2 = "World!";
// 	char 	*ret;
// 	char 	*ret2;
// 	char 	*ret42;
// 	// // ret	= ft_strnjoin(s1, s2, 8);
// 	// ret = ft_strjoin_at(s1, s2, 2);
// 	ret = ft_strdup("duplicate");
// 	ret2 = ft_strdup("duplicate2");
// 	ret42 = ft_strdup("duplicate3");
// 	// printf("%s\n", ret);
// 	// free(ret);
// 	ft_free(ret42);
// 	ft_free(ret);
// 	ft_free(ret2);
// 	delete_trash();
// 	ft_bzero(get_workers(), sizeof(t_trashman));
// 	// system("leaks a.out");
// }
