/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:55:59 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/11 16:56:57 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_lstlast(t_node *lst)
{
	t_node	*p;

	p = lst ;
	if (p == NULL)
		return (NULL);
	while (p -> next != NULL)
	{
		p = p -> next;
	}
	return (p);
}

void	add_back(t_node **lst, t_node *new)
{
	t_node	*p;

	p = ft_lstlast(*lst);
	if (p == NULL)
	{
		*lst = new;
		return ;
	}
		p -> next = new;
}

t_node	*ft_lstnew(void *content, char *type, int space)
{
	t_node	*p;

	p = malloc(sizeof(t_node));
	if (!p)
		exit (0);
	p -> data = (char *)content;
	p -> type = type;
	p -> space = space;
	p -> next = NULL;
	return (p);
}
