/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:19:05 by fforster          #+#    #+#             */
/*   Updated: 2024/04/04 19:11:53 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		i;

	if (!lst)
		return (0);
	tmp = lst;
	i = 0;
	while (tmp != 0)
	{
		tmp = tmp->next;
		i++;
	}
	if (i == 0)
		i++;
	return (i);
}
// #include <stdio.h>
// int main()
// {
// 	printf("%d", ft_lstsize(ft_lstnew("asgjhjm")));
// }