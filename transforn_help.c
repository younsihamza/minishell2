/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforn_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:25:31 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/23 15:22:11 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_help(t_help_var *v, t_node **rot)
{
	v->r = 0;
	if (ft_strcmp(rot[v->i]->type, "OP_VR") == 0)
	{
		v->splitvar = ft_split(rot[v->i]->data, ' ');
		if (v->splitvar != NULL)
		{
			while (v->splitvar[v->r])
			{
				v->tmp2d = v->command;
				v->command = ft_join2d(v->command, v->splitvar[v->r]);
				free(v->tmp2d);
				v->r++;
			}
			free(v->splitvar);
		}
	}
	else
	{
		v->tmp2d = v->command;
		v->command = ft_join2d(v->command, ft_strdup(rot[v->i]->data));
		free(v->tmp2d);
	}
}

void	convert_cmd(t_data *d, t_help_var *v, t_node **rot)
{
	v->r = 0;
	v->command = NULL;
	v->splitvar = NULL;
	while (rot[v->i])
	{
		while (rot[v->i])
		{
			if (ft_strcmp("OP_PIPE", rot[v->i]->type) != 0)
			{
				if (ft_strcmp(rot[v->i]->type, "OP_FILE") != 0)
					cmd_help(v, rot);
				else
					v->i++;
			}
			else
				break ;
			v->i++;
		}
				d->cmd[v->j] = v->command;
				v->command = NULL;
				v->j++;
		if (rot[v->i] != NULL)
			v->i++;
	}
}

void	help_table(t_help_var *v, t_node **rot, t_data	*d, char ***type)
{
	if (ft_strcmp("OP_PIPE", rot[v->i]->type) == 0
		|| rot[v->i +1] == NULL)
	{
		d->deriction[v->j] = v->file;
		d->typefile[v->j] = *type;
		v->file = NULL;
		*type = NULL;
		v->j++;
	}
}

void	table_deriction(t_help_var *v, t_node **rot, t_data	*d, char **type)
{
	char	**tmptype;

	while (rot[v->i])
	{
		if (ft_strcmp(rot[v->i]->type, "OP_FILE") == 0)
		{
			v->tmp2d = v->file;
			v->file = ft_join2d(v->file, ft_strjoin(rot[v->i]->data,
						rot[v->i + 1]->data));
			tmptype = type;
			type = ft_join2d(type, rot[v->i + 1]->type);
			if (ft_search(rot[v->i]->data, '<') == 2)
				d->status[v->j] = rot[v->i + 1]->status;
			if (v->tmp2d != NULL)
				free(v->tmp2d);
			if (tmptype != NULL)
				free(tmptype);
			v->i++;
		}
		help_table(v, rot, d, &type);
		v->i++;
	}
}
