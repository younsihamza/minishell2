/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:29:05 by hyounsi           #+#    #+#             */
/*   Updated: 2023/04/06 22:50:21 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*limet(char *l)
{
	int	i;

	i = 0;
	while (ft_strchr(" <", l[i]) != 0)
		i++;
	return (l + i);
}

int	ft_search(char *word, char to_find)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (word[i])
	{
		if (word[i] == to_find)
			len++;
		i++;
	}
	return (len);
}

char	**heredoc(char *stop)
{
	char	**value;
	char	**tmp;
	char	*p;

	tmp = NULL;
	value = NULL;
	while (1)
	{
		p = readline("herecod>");
		if (ft_strcmp(stop, p) == 0)
			break ;
		else
		{
			tmp = value;
			value = ft_join2d(value, p);
			free(tmp);
		}
	}
	if (p)
		free(p);
	return (value);
}

void	free2d(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
}

char	***checkherecode(char ***deriction, int len)
{
	char	***heredoctable;
	int		i;
	int		j;

	i = 0;
	heredoctable = ft_calloc(sizeof(char **), len);
	if (!heredoctable)
		exit(0);
	while (deriction[i] != NULL)
	{
		j = 0;
		while (deriction[i][j])
		{
			if (ft_search(deriction[i][j], '<') == 2)
			{
				if (heredoctable[i] != NULL)
					free2d(heredoctable[i]);
				heredoctable[i] = heredoc(limet(deriction[i][j]));
			}
			j++;
		}
		i++;
	}
	return (heredoctable);
}
