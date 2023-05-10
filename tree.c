/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:58:27 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/10 10:27:09 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_node(t_node **root, int *i, char *hold)
{
	int		j;

	j = *i + 1;
	while (root[j] != NULL)
	{
		if (ft_strncmp(root[j]->type, "OP_PIPE", 7) != 0
			&& root[j]->space == 0
			&& ft_strncmp(root[j]->type, "OP_FILE", 7) != 0)
		{
			hold = root[*i]->data;
			root[*i]->data = ft_strjoin(root[*i]->data, root[j]->data);
			if(ft_strcmp(root[j]->type, "DOUBLE") == 0 || ft_strcmp(root[*i]->type, "DOUBLE") == 0 || ft_strcmp(root[j]->type, "SINGLE") == 0 || ft_strcmp(root[*i]->type, "SINGLE") == 0 )
				root[*i]->status = 1;
			free(hold);
		}
		else
		{
			if(ft_strcmp(root[*i]->type, "DOUBLE") == 0 || ft_strcmp(root[*i]->type, "SINGLE") == 0 )
				root[*i]->status = 1;
			else
				root[*i]->status = 0;
			break ;
		}
		j++;
	}
	return (j);
}

t_node	**edit_rot(t_node **root, int len)
{
	int		i;
	int		j;
	char	*hold;
	int		cort;
	t_node	**list;

	i = 0;
	j = 0;
	hold = NULL;
	cort = 0;
	list = ft_calloc(sizeof (t_node *), len + 1);
	while (root[i] != NULL)
	{
		j = i + 1;
		if (ft_strncmp(root[i]->type, "OP_PIPE", 7) != 0
			&& ft_strncmp(root[i]->type, "OP_FILE", 7) != 0)
		{
			j = join_node(root, &i, hold);
		}
		list[cort++] = root[i];
		i = j;
	}
	return (list);
}

t_tree	*ft_insert(t_node **head)
{
	t_node	*ptr;
	t_tree	*root;

	ptr = *head;
	root = NULL;
	while (ptr != NULL)
	{
		if (ft_strncmp(ptr->type, "OP_PIPE", 7) == 0)
			root = insert(root, ptr);
		ptr = ptr->next;
	}
	ptr = *head;
	while (ptr != NULL)
	{
		root = insert(root, ptr);
		ptr = ptr->next;
	}
	return (root);
}

void	ft_func(t_tree *root, int len, t_env *envir, char *pathHome)
{
	t_node	**rot;
	int		a;
	t_node	**list;

	a = 0;
	rot = ft_calloc(sizeof(t_node *), len + 1);
	makestack(root, rot, &a);
	ft_inorder(rot, envir->envv);
	list = edit_rot(rot, len);
	transform_cmd(list, envir->envv, envir->declare, pathHome);
	free(rot);
	free(list);
}

t_tree	*bulid_tree(t_node *head, t_env *envir, char *pathHome)
{
	t_node	*ptr;
	t_tree	*root;
	t_tree	**queue;
	int		len;

	ptr = head;
	queue = NULL;
	root = ft_insert(&head);
	len = len_list(head);
	if (len == 0)
		return (NULL);
	queue = make_queue(len, root);
	if (check_error_parser(queue, len) != 0)
	{
		free(queue);
		free_tree(root);
		free_head(head);
		return (NULL);
	}
	free(queue);
	ft_func(root, len, envir, pathHome);
	free_tree(root);
	free_head(head);
	return (NULL);
}
