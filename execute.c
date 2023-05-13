/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:49:39 by hyounsi           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/13 16:41:30 by hyounsi          ###   ########.fr       */
=======
/*   Updated: 2023/05/13 11:56:15 by ichouare         ###   ########.fr       */
>>>>>>> d72b434c1be88131493498da183cf6412bf69442
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dups(char **deriction, char **heredoctable, int test)
{
	t_help_var	v;

	v.heredoc = NULL;
	v.infile = NULL;
	v.outappend = NULL;
	v.outfile = NULL;
	v.i = 0;
	while (deriction[v.i])
	{
		find_file(&v, deriction,test);
		v.i++;
	}
	if (test == 1)
	{
		v.i = 0;
		out_file(&v);
		in_file(&v, heredoctable);
	}
}

void	build_in_parent(t_data *var, int i, t_vars **env, t_vars **declare)
{
	if (ft_strcmp(var->cmd[i][0], "cd") == 0)
	{
		if (var->op[i] == NULL)
			cd(var->cmd[i][1], var);
	}
	else if (ft_strcmp(var->cmd[i][0], "exit") == 0)
	{
		if (var->op[0] == NULL)
			exit(write(2, "exit\n", 5));
	}
	else if (ft_strcmp(var->cmd[i][0], "unset") == 0)
	{
		ft_unset(var->cmd[i], env);
		ft_unset_declare(var->cmd[i], declare);
	}
	else if (ft_strcmp(var->cmd[i][0], "export") == 0)
		if (var->op[0] == NULL)
			ft_export(var->cmd[i], env, declare);
}

void	pipe_tool(t_help_var *v, t_data *var)
{
	while (var->op[v->i])
	{
		if (ft_strncmp(var->op[v->i]->type, "OP_PIPE", 7) == 0)
			v->lenpipe++;
		v->i++;
	}
	v->fds = malloc(sizeof(int *) * v->lenpipe);
	if (!v->fds)
		exit(0);
	v->i = 0;
	while (v->i < v->lenpipe)
	{
		v->fds[v->i] = malloc(sizeof(int) * 2);
		if (!v->fds[v->i])
			exit(0);
		pipe(v->fds[v->i]);
		v->i++;
	}
	v->i = 0;
}

void	child_parte(t_data *var, t_vars **env, t_vars **declare, t_help_var *v)
{
	g_s[0] = 1;
	v->id = fork();
	if (v->id < 0)
		return;
	if (v->id == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (var->op[v->i] != NULL)
			if (ft_strncmp(var->op[v->i]->type, "OP_PIPE", 7) == 0)
				dup2(v->fds[v->pipeincrement][1], 1);
		if (var->deriction[v->i] != NULL)
			dups(var->deriction[v->i], var->heredoc[v->i], 1);
		if (v->i - 1 >= 0 && v->pipeincrement > 0)
			if (ft_strncmp(var->op[v->i - 1]->type, "OP_PIPE", 7) == 0)
				dup2(v->fds[v->pipeincrement - 1][0], 0);
		ft_close(v->fds, v->lenpipe);
		cmd1(var->cmd[v->i], env, declare);
		exit(127);
	}
	if (var->op[v->i] != NULL)
		if (ft_strncmp(var->op[v->i]->type, "OP_PIPE", 7) == 0)
			v->pipeincrement++;
}

void	execute(t_data *var, t_vars **env, t_vars **declare)
{
	t_help_var	v;

	v.pipeincrement = 0;
	v.lenpipe = 0;
	v.i = 0;
	pipe_tool(&v, var);

	while (v.i <= v.lenpipe)
	{
		if (var->cmd[v.i] != NULL)
		{
			if (ft_strcmp(var->cmd[v.i][0], "cd") == 0
				|| ft_strcmp(var->cmd[v.i][0], "exit") == 0
				|| (ft_strcmp(var->cmd[v.i][0], "export") == 0
				&& var->cmd[v.i][1] != NULL)
				|| ft_strcmp(var->cmd[v.i][0], "unset") == 0)
				{
				build_in_parent(var, v.i, env, declare);
				}
			else
				child_parte(var, env, declare, &v);
		}
		v.i++;
	}
	help_me(&v);
}
