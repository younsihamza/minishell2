/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:51:12 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/11 16:51:41 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_inorder(t_tree *root, t_vars *env)
{
	if (root == NULL)
		return ;
	ft_inorder(root->right, env);
	ft_expand(root, env);
	ft_inorder(root->left, env);
}
