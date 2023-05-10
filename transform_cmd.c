/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:59:57 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/10 19:11:26 by hyounsi          ###   ########.fr       */
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
}

void	convert_deriction(t_help_var *v, t_node **rot, t_data	*d)
{
	d->deriction = ft_calloc(sizeof(char **), v->len + 2);
	d->status = ft_calloc(sizeof(int),v->len + 1);
	v->i = 0;
	v->j = 0;
	v->file = NULL;
	while (rot[v->i])
	{
		if (ft_strcmp(rot[v->i]->type, "OP_FILE") == 0)
		{
			v->tmp2d = v->file;
			v->file = ft_join2d(v->file, ft_strjoin(rot[v->i]->data,
						rot[v->i + 1]->data));
			if(ft_search(rot[v->i]->data, '<') == 2)
				d->status[v->j] = rot[v->i + 1]->status;
			free(v->tmp2d);
			v->i++;
		}
		if ((ft_strcmp("OP_PIPE", rot[v->i]->type) == 0
				|| rot[v->i +1] == NULL )
			&& v->file != NULL)
		{
			d->deriction[v->j] = v->file;
			v->file = NULL;
			v->j++;
		}
		v->i++;
	}
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
}

void	transform_cmd(t_node **rot, t_vars *env,
		t_vars *declare, char *pathhome)
{
	t_help_var	v;
	t_data		d;

	v.r = 0;
	v.command = NULL;
	v.splitvar = NULL;
	convert_op(&v, rot, &d);
	v.i = 0;
	d.cmd = ft_calloc(sizeof(char **), v.len + 2);
	v.j = 0;
	convert_cmd(&d, &v, rot);
	convert_deriction(&v, rot, &d);
	d.heredoc = checkherecode(d.deriction, v.len + 2, d.status, env);
	d.pathhome = pathhome;
	v.i = 0;
	while (v.i <= v.len)
	{
		if (d.deriction[v.i] != NULL)
			dups(d.deriction[v.i], d.heredoc[v.i], 0);
		v.i++;
	}
	v.i = 0;
	ft_tolower(d.cmd);
	execute(&d, env, declare);
	
	kill_leaks(&v, &d);
}
