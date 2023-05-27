/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:29:05 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/27 12:37:19 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_s[3] = 0;
		g_s[1] = 1;
		close(0);
	}
}

void	heredoc_help(char ***value, char ***tmp)
{
	*tmp = NULL;
	*value = NULL;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

char	**heredoc(char *stop, int status, t_vars **env)
{
	char	**value;
	char	**tmp;
	char	*p;

	heredoc_help(&value, &tmp);
	while (1)
	{
		g_s[1] = 0;
		p = readline("heredoc>");
		if (!p || ft_strcmp(stop, p) == 0)
			break ;
		else
		{
			tmp = value;
			if (status == 1)
				value = ft_join2d(value, p);
			else
				value = ft_join2d(value, herdoc_expand(p,*env));
			if (tmp != NULL)
				free(tmp);
		}
	}
	if (p)
		free(p);
	return (value);
}

void	free2dherdoc(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}

char	***checkherecode(char ***deriction, int len, int *status, t_vars **env)
{
	t_help_var	var;

	var.i = 0;
	var.heredoctable = ft_calloc(sizeof(char **), len);
	while (var.i < len)
	{
		var.j = 0;
		if (deriction[var.i])
		{
			while (deriction[var.i][var.j])
			{
				if (ft_search(deriction[var.i][var.j], '<') == 2)
				{
					if (var.heredoctable[var.i] != NULL)
						free2dherdoc(var.heredoctable[var.i]);
					var.heredoctable[var.i] = heredoc(
							limet(deriction[var.i][var.j]), status[var.i], env);
				}
				var.j++;
			}
		}
		var.i++;
	}
	free(status);
	return (var.heredoctable);
}
