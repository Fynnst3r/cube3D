/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:47:55 by fforster          #+#    #+#             */
/*   Updated: 2024/04/05 15:38:24 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	void	*container;

	if (!lst || !f || !del)
		return (NULL);
	new = 0;
	while (lst)
	{
		container = f(lst->content);
		tmp = NULL;
		if (container)
			tmp = ft_lstnew(container);
		else
			del(container);
		if (!tmp)
		{
			ft_lstclear(&new, del);
			del(container);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&new, tmp);
	}
	return (new);
}
