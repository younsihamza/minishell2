/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:19:08 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/10 17:57:18 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*ft_envnew(void *content)
{
	t_vars	*p;

	p = malloc(sizeof(t_vars));
	if (!p)
		exit (0);
	p->data = (char *)content;
	p->next = NULL;
	return (p);
}

t_vars	*ft_lstlastenv(t_vars *lst)
{
	t_vars	*p;

	p = lst ;
	if (p == NULL)
		return (NULL);
	while (p->next != NULL)
	{
		p = p->next;
	}
	return (p);
}

void	add_envback(t_vars **lst, t_vars *new)
{
	t_vars	*p;

	p = ft_lstlastenv(*lst);
	if (p == NULL)
	{
		*lst = new;
		return ;
	}
		p->next = new;
}

t_vars	*get_env(char **env)
{
	int		i;
	t_vars	*vars;

	i = 0;
	vars = NULL;
	while (env[i])
	{
		add_envback(&vars, ft_envnew(ft_strdup(env[i])));
		i++;
	}
	return (vars);
}
