/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:29:05 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/21 16:05:45 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*limet(char *l)
{
	int	i;

	i = 0;
	while (ft_strchr("<", l[i]) != 0)
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

void handle_signal(int signum) {
    if (signum == SIGINT || signum == SIGQUIT) {
        close(0);
    }
}



char	**heredoc(char *stop,int status, t_vars **env)
{
	char	**value;
	char	**tmp;
	char	*p;
	tmp = NULL;
	value = NULL;
	signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);
	while (1 && test)
	{
		p = readline("heredoc>");
		if(p)
		{
			if (ft_strcmp(stop, p) == 0 || g_s[0] == 7)
				break ;
			else
			{
				tmp = value;
				if(status == 1)
					value = ft_join2d(value, p);
				else
					value = ft_join2d(value, herdoc_expand(p,*env));
				free(tmp);
			}	
		}else
			break;
	}
	if (p)
		free(p);
	test = 1;
	return (value);
}

void	free2d(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
}

char	***checkherecode(char ***deriction, int len,int *status, t_vars **env)
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
				heredoctable[i] = heredoc(limet(deriction[i][j]),status[i],env);
			}
			j++;
		}
		i++;
	}
	free(status);
	return (heredoctable);
}
