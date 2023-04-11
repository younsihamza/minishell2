/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:58:27 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/11 17:04:30 by ichouare         ###   ########.fr       */
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
	if (strcmp(root->tokn->type, "OP_VR") == 0)
		expand_one(&root->tokn->data, tmp, env);
	else if (strcmp(root->tokn->type, "DOUBLE") == 0)
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
t_node **edit_rot(t_node **root, int len)
{
    int i = 0;
    int j = 0;
    char *hold = NULL;
    int cort = 0;
    t_node **list = ft_calloc(sizeof(t_node*),len + 1);

    while(root[i] != NULL)
    {
        j = i + 1;
        if(ft_strncmp(root[i]->type,"OP_PIPE",7) != 0 &&ft_strncmp(root[i]->type,"OP_FILE",7) != 0)
        {
            while(root[j] != NULL)
                {
                    if(ft_strncmp(root[j]->type,"OP_PIPE",7) != 0 && root[j]->space == 0 
					&& ft_strncmp(root[j]->type,"OP_FILE",7) != 0 )
                    {
                        hold = root[i]->data;
                        root[i]->data = ft_strjoin(root[i]->data,root[j]->data);
                        free(hold);
                    }
					else
                        break;
                    j++;
                }
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
	root= NULL;
	while (ptr != NULL)
	{
		if (ft_strncmp(ptr->type, "OP_PIPE", 7) == 0 )
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

void	ft_func(t_tree *root, int len, t_vars *env, t_vars *declare, char *pathHome)
{
	t_node	**rot;
	int		a;
	t_node	**list;

	a = 0;
	rot = ft_calloc(sizeof(t_node*), len + 1);
	ft_inorder(root, env);
	makestack(root, rot, &a);
	list = edit_rot(rot, len);
	transform_cmd(list, env, declare, pathHome);
	free(rot);
	free(list);
}

t_tree	*bulid_tree(t_node *head, t_vars *env, t_vars *declare, char *pathHome)
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
	ft_func(root, len, env, declare, pathHome);
	free_tree(root);
	free_head(head);
	return (NULL);
}
