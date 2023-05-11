/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:29:28 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/11 20:45:12 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove(char **args, int *i, t_vars **vars)
{
	t_vars	*cur;
	t_vars	*prev;
	t_vars	*list;
	//int j = 0;

	cur = (*vars);
	list = cur;
	prev = cur;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, args[*i],
				ft_strlencher(cur->data, '=')) == 0)
		{
			list = cur;
			prev->next = cur->next;
			free(list->data);
			list->data = NULL;
			free(list);
			list = NULL;
		}
		else
			prev = cur;
		cur = cur->next;
	}
}

void	ft_unset(char **args, t_vars *vars)
{
	int		i;

	if (args[1] == NULL || vars == NULL)
		return ;
	i = 1;
	while (args[i])
	{
		if (is_alpha(args[i]) == -1)
			g_s[1] = printf("unset: `%s': not a valid identifier\n", args[i]);
		else
			ft_remove(args, &i, &vars);
		i++;
	}
}

void	ft_unset_declare(char **args, t_vars **vars)
{
	int		i;

	if (args[1] == NULL || vars == NULL)
		return ;
	i = 1;
	while (args[i])
	{
		if (is_alpha(args[i]) != -1)
			ft_remove(args, &i, vars);
		i++;
	}
}

void	ft_modify(char *str, t_vars **declare)
{
	char	*buffer1;

	buffer1 = NULL;
	if ((ft_strlen(str) == 1 && str[0] == '=') || str[0] == '=')
	{
		g_s[1] = printf("bash: export: `%s': not a valid identifier\n", str);
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
