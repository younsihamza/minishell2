/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:29:28 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/10 15:54:40 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_content(char *str)
{
	char	*tmp;
	char	*buffer1;
	char	*buffer2;

	tmp = NULL;
	buffer1 = NULL;
	buffer2 = NULL;
	buffer1 = ft_substr(str, 0, ft_strlencher(str, '=') + 1);
	buffer2 = ft_substr(str, ft_strlencher(str, '=') + 1, ft_strlen(str));
	tmp = buffer2;
	buffer2 = ft_strjoin("\"", buffer2);
	free(tmp);
	tmp = buffer2;
	buffer2 = ft_strjoin(buffer2, "\"");
	free(tmp);
	tmp = buffer1;
	buffer1 = ft_strjoin(buffer1, buffer2);
	free(buffer2);
	free(tmp);
	return (buffer1);
}

void	ft_add_new(t_vars **declare, char *str, char *buffer1)
{
	t_vars	*cur;

	cur = *declare;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, str, ft_strlencher(cur->data, '=')) == 0)
		{
			if (ft_strchr(str, '=') == 0)
			{
				free(buffer1);
				return ;
			}
			free(cur->data);
			cur->data = buffer1;
			return ;
		}
	cur = cur->next;
	}
	add_envback(declare, ft_envnew(buffer1));
}

void	ft_unset(char **args, t_vars *vars)
{
	t_vars	*cur;
	t_vars	*prev;
	t_vars	*list;
	int		i;

	if (args[1] == NULL || vars == NULL)
		return ;
	i = 1;
	//ft_remove(args, i);
	while (args[i])
	{
		cur = vars;
		list = cur;
		prev = cur;
		while (cur != NULL)
		{
			if (is_alpha(args[i]) == -1)
			{
				printf("unset: `%s': not a valid identifier\n", args[i]);
				break ;
			}
			if (ft_strncmp(cur->data, args[1],
					ft_strlencher(cur->data, '=')) == 0)
			{
				list = cur;
				prev->next = cur->next;
				free(list->data);
				free(list);
			}
			else
				prev = cur;
			cur = cur->next;
		}
		i++;
	}
}

void	ft_modify(char *str, t_vars **declare)
{
	char	*buffer1;

	buffer1 = NULL;
	if ((ft_strlen(str) == 1 && str[0] == '=') || str[0] == '=')
	{
		printf("bash: export: `%s': not a valid identifier\n", str);
		return ;
	}
	if (ft_strchr(str, '=') != 0)
		buffer1 = ft_content(str);
	else
		buffer1 = ft_strdup(str);
	ft_add_new(declare, str, buffer1);
}

void	ft_modify_env(char *str, t_vars *env)
{
	t_vars	*cur;

	cur = env;
	if ((ft_strlen(str) == 1 && str[0] == '=') || str[0] == '=')
		return ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, str, ft_strlencher(str, '=')) == 0)
		{
			free(cur->data);
			cur->data = ft_strdup(str);
			return ;
		}
		cur = cur->next;
	}
	add_envback(&env, ft_envnew(ft_strdup (str)));
}
