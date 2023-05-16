/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:48:16 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/16 15:22:15 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	**make_queue(int len, t_tree *root)
{
	int		rear;
	int		front;
	t_tree	**queue;

	rear = 0;
	front = 0;
	queue = malloc(sizeof(t_tree *) * len);
	if (!queue)
		exit(0);
	queue[rear] = root;
	rear++;
	while (front != rear)
	{
		if (queue[front]->right != NULL)
			queue[rear++] = queue[front]->right;
		if (queue[front]->left != NULL)
			queue[rear++] = queue[front]->left;
		front++;
	}
	return (queue);
}

void	free_head(t_node *head)
{
	t_node	*ptr;

	ptr = NULL;
	while (head != NULL)
	{
		ptr = head;
		free(ptr->data);
		head = head->next;
		free(ptr);
	}
}

void	makestack(t_tree *root, t_node **rot, int *i)
{
	if (root == NULL)
		return ;
	makestack(root->right, rot, i);
	rot[*i] = root->tokn;
	*i += 1;
	makestack(root->left, rot, i);
}

int	check_error_parser(t_tree **q, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (ft_strncmp(q[i]->tokn->type, "OP_PIPE", 8) == 0)
			if (q[i]->right == NULL || q[i]->left == NULL)
				return (write(2, "ERROR parser\n", 13));
		if (ft_strncmp(q[i]->tokn->type, "OP_FILE", 8) == 0)
		{
			if (q[i]->left == NULL)
				return (write(2, "ERROR parser\n", 13));
			else if(ft_strncmp(q[i]->left->tokn->type, "OP_FILE", 8) == 0)
				return (write(2, "ERROR parser\n", 13));
		}
		i++;
	}
	return (0);
}

void	free_tree(t_tree *root)
{
	if (root == NULL)
		return ;
	free_tree(root->right);
	free_tree(root->left);
	free (root);
}
