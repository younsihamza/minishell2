/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:51:12 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/12 15:30:19 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand(t_tree *root, t_vars *env)
{
	t_node	*str;
	t_node	*ptr;
	char	*tmp;
	char	*tokn;

	str = NULL;
	ptr = NULL;
	tmp = NULL;
	if (ft_strcmp(root->tokn->type, "OP_VR") == 0)
		expand_one(&root->tokn->data, tmp, env);
	else if (ft_strcmp(root->tokn->type, "DOUBLE") == 0)
	{
		ptr = expand_two(&root->tokn->data, &str, env);
		tokn = ft_calloc(sizeof(char), 2);
		while (ptr != NULL)
		{
			if (ptr->data != NULL)
				join_data(&ptr->data, tmp, &tokn);
			str = ptr;
			ptr = ptr->next;
			free(str);
		}
		free(root->tokn->data);
		root->tokn->data = tokn;
	}
}

void	ft_inorder(t_tree *root, t_vars *env)
{
	if (root == NULL)
		return ;
	ft_inorder(root->right, env);
	ft_expand(root, env);
	ft_inorder(root->left, env);
}
