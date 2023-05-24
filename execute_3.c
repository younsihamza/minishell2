/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:25:49 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/24 17:38:26 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dups(char **deriction, char **heredoctable, int test, char **typefile)
{
	t_help_var	v;

	v.heredoc = NULL;
	v.infile = NULL;
	v.outappend = NULL;
	v.outfile = NULL;
	v.i = 0;
	while (deriction[v.i])
	{
		if (find_file(&v, deriction, test, typefile) == 1)
			break ;
		v.i++;
	}
	if (test == 1)
	{
		v.i = 0;
		out_file(&v);
		in_file(&v, heredoctable);
	}
}

char	*delimet(char *l)
{
	int	i;

	i = 0;
	while (ft_strchr(" <>", l[i]) != 0)
		i++;
	return (l + i);
}

int	is_empty(t_help_var *v, char **deriction, int test, char **typefile)
{
	if (ft_strcmp(typefile[v->i], "OP_VR") == 0 && (ft_strchr(deriction[v->i],
				' ') == 1 || ft_strlen(delimet(deriction[v->i])) == 0))
	{
		if (test == 0)
		{
			g_s[1] = 1;
			write(2, "minishell: ambiguous redirect\n", 30);
		}
		else
			exit(1);
		return (1);
	}
	return (0);
}

int	make_infile(t_help_var *v, char **deriction, int test)
{
	if (ft_search(deriction[v->i], '<') == 2)
			v->heredoc = delimet(deriction[v->i]);
	else
	{
		v->infile = delimet(deriction[v->i]);
		v->heredoc = NULL;
		v->fd = open(v->infile, O_RDONLY);
		close(v->fd);
		if (v->fd == -1)
		{
			if (test == 0)
			{
				g_s[1] = 1;
				write(2, "minishell: ", 11);
				write(2, v->infile, ft_strlen(v->infile));
				write(2, " : No such file or directory\n", 29);
			}
			else
				exit(1);
			return (1);
		}
		close(v->fd);
	}
	return (0);
}
