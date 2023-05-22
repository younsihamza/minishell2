/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:39:19 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/22 16:37:38 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strimplement(char *str, char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (*(s1 + j))
	{
		*(str + i) = *(s1 + j);
		j++;
		i++;
	}
	j = 0;
	while (*(s2 + j))
	{
		*(str + i) = *(s2 + j);
		j++;
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;

	str = NULL;
	if (!s1 || !s2)
		return (str);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		exit (0);
	strimplement(str, s1, s2);
	return (str);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	r;
	char	*p;

	j = 0 ;
	i = start ;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p = ft_calloc(sizeof(char), 1);
		return (p);
	}
	if (ft_strlen(s + start) > len)
		r = len;
	else
		r = ft_strlen(s + start);
	p = ft_calloc(sizeof(char), r + 1);
	if (!p)
		return (NULL);
	while (j < r)
		*(p + j++) = *(s + i++);
	return (p);
}

t_tree	*insert(t_tree *root, t_node *ptr)
{
	if (root == NULL)
		root = create_node_tree(ptr);
	else if (root->tokn->i < ptr->i)
		root->left = insert(root->left, ptr);
	else if (root->tokn->i > ptr->i)
		root->right = insert(root->right, ptr);
	return (root);
}

char	*get_env_arr(char *find, t_vars *env)
{
	t_vars	*ptr;
	int		len;

	ptr = env;
	while (ptr != NULL)
	{
		len = ft_strlencher(ptr->data, '=');
		if (len < (int)ft_strlen(find))
			len = (int)ft_strlen(find);
		if (ft_strncmp(ptr->data, find, len) == 0)
			return (ptr->data + ft_strlen(find) + 1);
		ptr = ptr->next;
	}
	return (NULL);
}
