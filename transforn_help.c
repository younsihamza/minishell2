/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforn_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:25:31 by hyounsi           #+#    #+#             */
/*   Updated: 2023/04/06 22:26:57 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_help(t_help_var *v, t_node **rot)
{
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
		if (v->command != NULL)
		{
			d->cmd[v->j] = v->command;
			v->command = NULL;
			v->j++;
		}
		if (rot[v->i] != NULL)
			v->i++;
	}
}
