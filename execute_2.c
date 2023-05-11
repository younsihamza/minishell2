/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:49:28 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/11 15:56:14 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_file(t_help_var *v, char **deriction)
{
	if (ft_search(deriction[v->i], '<'))
	{
		if (ft_search(deriction[v->i], '<') == 2)
			v->heredoc = delimet(deriction[v->i]);
		else
		{
			v->infile = delimet(deriction[v->i]);
			v->heredoc = NULL;
			v->fd = open(v->infile, O_RDONLY);
			if (v->fd == -1)
				exit(write(2, "No such file or directory\n", 27));
			close(v->fd);
		}
	}
	else if (ft_search(deriction[v->i], '>'))
	{
		if (ft_search(deriction[v->i], '>') == 2)
			v->outappend = delimet(deriction[v->i]);
		else
		{
			v->outfile = delimet(deriction[v->i]);
			close(open(v->outfile, O_CREAT | O_TRUNC, 0644));
			v->outappend = NULL;
		}
	}
}

void	in_file(t_help_var *v, char **heredoctable)
{
	if (v->heredoc != NULL)
	{
		v->fd1 = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0700);
		while (heredoctable[v->i])
			ft_putstr(heredoctable[v->i++], v->fd1);
		close(v->fd1);
		v->fd1 = open("/tmp/heredoc", O_RDONLY);
		dup2(v->fd1, 0);
	}
	else if (v->infile != NULL)
	{
		v->fd1 = open(v->infile, O_RDONLY, 0644);
		if (v->fd1 == -1)
			exit(write(2, "No such file or directory", 27));
		dup2(v->fd1, 0);
	}
}

int	out_file(t_help_var *v)
{
	if (v->outappend != NULL)
	{
		v->fd2 = open(v->outappend, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(v->fd2, 1);
	}
	else if (v->outfile != NULL)
	{
		v->fd2 = open(v->outfile, O_CREAT | O_WRONLY | O_TRUNC, 777);
		if (v->fd2 == -1)
			write(2, "filed\n", 6);
		dup2(v->fd2, 1);
		close(v->fd2);
	}
	return (v->fd2);
}

void	help_me(t_help_var *v)
{
	while ((waitpid(0, &g_s[1], 0)) != -1)
		ft_close(v->fds, v->lenpipe);
	if(g_s[1] != 0)
		g_s[1] = 1;
	g_s[0] = 0;
	v->i = 0;
	while (v->i < v->lenpipe)
		free(v->fds[v->i++]);
	free(v->fds);
}
