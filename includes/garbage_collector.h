/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:34:41 by fforster          #+#    #+#             */
/*   Updated: 2025/02/17 12:31:36 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "cub3D.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <strings.h>

typedef struct s_list	t_list;

typedef struct s_trashnode
{
	void				*totrash;
	struct s_trashnode	*next;
}						t_trashnode;

typedef struct s_trashman
{
	t_trashnode	*head;
	t_trashnode	*tail;
	size_t		worker_num;
}				t_trashman;

//garbage_start.c
t_trashman	*init_garbage_collector(void);
t_trashman	*get_workers(void);
//ft_malloc.c
void		*ft_malloc(size_t size);
void		add_trash_top(void *pointer);
t_trashnode	*create_trash_node(void *pointer);

//free.c
void		delete_trash(void);
void		ft_free(void *pointer);

#endif