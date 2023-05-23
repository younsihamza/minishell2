/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:59:57 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/23 15:22:07 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_op(t_help_var *v, t_node **rot, t_data	*d)
{
	v->j = 0;
	v->len = 0;
	v->i = 0;
	while (rot[v->i])
	{
		if (ft_strcmp("OP_PIPE", rot[v->i]->type) == 0)
			v->len++;
		v->i++;
	}
	d->op = ft_calloc(sizeof(t_node *), v->len + 2);
	v->i = 0;
	while (rot[v->i])
	{
		if (ft_strcmp("OP_PIPE", rot[v->i]->type) == 0)
		{
			d->op[v->j] = rot[v->i];
			v->j++;
		}
		v->i++;
	}
	v->i = 0;
	v->j = 0;
}

void	convert_deriction(t_help_var *v, t_node **rot, t_data *d)
{
	d->typefile = NULL;
	d->deriction = ft_calloc(sizeof(char **), v->len + 2);
	d->typefile = ft_calloc(sizeof(char **), v->len + 2);
	d->status = ft_calloc(sizeof(int), v->len + 1);
	v->i = 0;
	v->j = 0;
	v->file = NULL;
	v->tmp2d = NULL;
	table_deriction(v, rot, d, NULL);
}

void	free_table(char ***table, t_help_var *v)
{
	int	i;

	i = 0;
	while (i <= v->len)
	{
		if (table[i])
		{
			free2d(table[i]);
			free(table[i]);
		}
		i++;
	}
	free(table);
}

void	kill_leaks(t_help_var *v, t_data *d)
{
	v->i = 0;
	free_table(d->heredoc, v);
	free_table(d->deriction, v);
	free(d->op);
	while (d->cmd[v->i])
	{
		free2d(d->cmd[v->i]);
		free(d->cmd[v->i]);
		v->i++;
	}
	free(d->cmd);
	v->i = 0;
	while (d->typefile[v->i])
	{
		free(d->typefile[v->i]);
		v->i++;
	}
	free(d->typefile);
}

void	transform_cmd(t_node **rot, t_vars **env,
		t_vars **declare, char *pathhome)
{
	t_help_var	v;
	t_data		d;

	convert_op(&v, rot, &d);
	d.cmd = ft_calloc(sizeof(char **), v.len + 2);
	convert_cmd(&d, &v, rot);
	convert_deriction(&v, rot, &d);
	d.heredoc = checkherecode(d.deriction, v.len + 2, d.status, env);
	if (g_s[3] == 0)
	{
		kill_leaks(&v, &d);
		return ;
	}
	d.pathhome = pathhome;
	v.i = 0;
	while (v.i <= v.len)
	{
		if (d.deriction[v.i] != NULL)
			dups(d.deriction[v.i], d.heredoc[v.i], 0, d.typefile[v.i]);
		v.i++;
	}
	v.i = 0;
	ft_tolower(d.cmd);
	execute(&d, env, declare);
	kill_leaks(&v, &d);
}
