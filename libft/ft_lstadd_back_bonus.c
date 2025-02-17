/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:03:18 by fforster          #+#    #+#             */
/*   Updated: 2024/04/03 14:42:34 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!lst || !new)
		return ;
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	t_list *l = ((void *)0);
//         t_list *n = ft_lstnew(ft_strdup("OK"));
//         ft_lstadd_back(&l, n);
//         if (l == n && !strcmp(l->content, "OK"))
//         {
// 			free(l->next);
// 			free(l);
// 			printf("wow u so cool");
//         }
//         free(l->next);
//         free(l);
// 		printf("u succ");
// }