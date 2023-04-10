/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:47:34 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/10 17:54:27 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr(char *str, char a)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen2d(char **s1)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	i;
	void	*p;

	i = 0;
	p = malloc(size * nitems);
	if (!p)
		exit (0);
	while (i < nitems * size)
	{
		*(char *)(p + i) = '\0';
		i++;
	}
	return (p);
}

char	**ft_join2d(char **env, char *var)
{
	char	**p;
	int		i;

	if (var == NULL)
		return (env);
	if (env == NULL)
	{
		p = ft_calloc(sizeof(char *), 2);
		p[0] = var;
		return (p);
	}
	p = ft_calloc(sizeof(char *), ft_strlen2d(env) + 2);
	i = 0;
	while (env[i])
	{
		p[i] = env[i];
		i++;
	}
	p[i] = var;
	return (p);
}

int	len_list(t_node *head)
{
	int	i;

	i = 0;
	while (head != NULL)
	{
		i++;
		head = head->next;
	}
	return (i);
}
