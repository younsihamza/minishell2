/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:49:39 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/27 14:44:02 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_in_parent(t_data *var, int i, t_vars **env, t_vars **declare)
{
	if (ft_strcmp(var->cmd[i][0], "cd") == 0)
	{
		if (var->op[i] == NULL)
			cd(var->cmd[i][1], var, env, declare);
	}
	else if (ft_strcmp(var->cmd[i][0], "exit") == 0)
	{
		if (var->op[0] == NULL)
			ft_exit(var->cmd[i], env, declare);
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
	v->pipeincrement = 0;
	v->lenpipe = 0;
	v->i = 0;
	g_s[2] = 0;
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
		v->fds[v->i] = ft_calloc(sizeof(int), 2);
		if (pipe(v->fds[v->i]) == -1)
			exit(0);
		v->i++;
	}
	v->i = 0;
}

void	files(t_data *var, t_help_var *v)
{
	if (var->op[v->i] != NULL)
		if (ft_strncmp(var->op[v->i]->type, "OP_PIPE", 7) == 0)
			if (dup2(v->fds[v->pipeincrement][1], 1) == -1)
				exit(0);
	if (var->deriction[v->i] != NULL)
		dups(var->deriction[v->i], var->heredoc[v->i],
			1, var->typefile[v->i]);
	if (v->i - 1 >= 0 && v->pipeincrement > 0)
		if (ft_strncmp(var->op[v->i - 1]->type, "OP_PIPE", 7) == 0)
			if (dup2(v->fds[v->pipeincrement - 1][0], 0) == -1)
				exit(0);
}

void	child_parte(t_data *var, t_vars **env, t_vars **declare, t_help_var *v)
{
	g_s[0] = 1;
	v->pidprocess = &g_s[1];
	signal(SIGINT, &handle_new);
	signal(SIGQUIT, &handle_new);
	v->id = fork();
	if (v->id < 0)
		return ;
	v->lastprose = v->id;
	if (v->id == 0)
	{
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		files(var, v);
		ft_close(v->fds, v->lenpipe);
		cmd1(var->cmd[v->i], env, declare);
		exit(1);
	}
	if (var->op[v->i] != NULL)
		if (ft_strncmp(var->op[v->i]->type, "OP_PIPE", 7) == 0)
			v->pipeincrement++;
}

void	execute(t_data *var, t_vars **env, t_vars **declare)
{
	t_help_var	v;

	v.pidprocess = &g_s[1];
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
				v.pidprocess = NULL;
			}
			else
				child_parte(var, env, declare, &v);
		}
		v.i++;
	}
	help_me(&v);
}
