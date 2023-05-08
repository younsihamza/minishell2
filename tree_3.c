/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:51:12 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/08 13:25:00 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand(t_node *rot, t_vars *env)
{
	t_node	*str;
	t_node	*ptr;
	char	*tmp;
	char	*tokn;

	str = NULL;
	ptr = NULL;
	tmp = NULL;
	if (ft_strcmp(rot->type, "OP_VR") == 0)
		expand_one(&rot->data, tmp, env);
	else if (ft_strcmp(rot->type, "DOUBLE") == 0)
	{
		ptr = expand_two(&rot->data, &str, env);
		tokn = ft_calloc(sizeof(char), 2);
		while (ptr != NULL)
		{
			if (ptr->data != NULL)
				join_data(&ptr->data, tmp, &tokn);
			str = ptr;
			ptr = ptr->next;
			free(str);
		}
		free(rot->data);
		rot->data = tokn;
	}
}

void	ft_inorder(t_node **rot, t_vars *env)
{
	int	i;

	i = 0;
	while (rot[i] != NULL)
	{
		if (ft_strcmp((rot[i])->data, "<<" ) == 0)
			i++;
		else
			ft_expand(rot[i], env);
		i++;
	}
}
