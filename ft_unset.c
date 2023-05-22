/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:29:28 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/22 18:39:01 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addback_r(t_vars **list, t_vars *new)
{
	t_vars	*hold;

	hold = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (hold->next != NULL)
		hold = hold->next;
	hold->next = new;
}

void	ft_remove(char **args, int *i, t_vars **vars)
{
	t_vars	*cur;
	t_vars	*newlist;
	t_vars	*hold;
	t_vars	*tmp;

	cur = (*vars);
	hold = NULL;
	newlist = NULL;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, args[*i],
				ft_strlencher(cur->data, '=')) != 0)
		{
			hold = cur;
			cur = cur->next;
			hold->next = NULL;
			addback_r(&newlist, hold);
		}
		else
		{
			tmp = cur;
			cur = cur->next;
			if (tmp != NULL)
			{
				free(tmp->data);
				free(tmp);
			}
		}	
	}
	*vars = newlist;
}

void	ft_unset(char **args, t_vars **vars)
{
	int		i;

	if (args[1] == NULL || vars == NULL)
		return ;
	i = 1;
	while (args[i])
	{
		if (is_alpha(args[i]) == -1 || ft_strlen(args[i]) == 0)
		{
			g_s[1] = 1;
			printf("unset: `%s': not a valid identifier\n", args[i]);
		}
		else
			ft_remove(args, &i, vars);
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

char	*ft_content_plus(char *str)
{
	char	*tmp;
	char	*buffer1;
	char	*buffer2;

	tmp = NULL;
	buffer1 = NULL;
	buffer2 = NULL;
	buffer1 = ft_substr(str, 0, ft_strlencher(str, '=') - 1);
	tmp = buffer1;
	buffer1 = ft_strjoin(buffer1, "=");
	free(tmp);
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

char	*ft_content_env(char *str)
{
	char	*tmp;
	char	*buffer1;
	char	*buffer2;

	tmp = NULL;
	buffer1 = NULL;
	buffer2 = NULL;
	buffer1 = ft_substr(str, 0, ft_strlencher(str, '=') - 1);
	tmp = buffer1;
	buffer1 = ft_strjoin(buffer1, "=");
	free(tmp);
	buffer2 = ft_substr(str, ft_strlencher(str, '=') + 1, ft_strlen(str));
	tmp = buffer1;
	buffer1 = ft_strjoin(buffer1, buffer2);
	free(buffer2);
	free(tmp);
	return (buffer1);
}

void	ft_modify(char *str, t_vars **declare)
{
	char	*buffer1;
	int		test_plus;

	buffer1 = NULL;
	test_plus = 0;
	if (ft_test_var(str, ft_strlencher(str, '=')) == 1)
	{
		g_s[1] = 1;
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return ;
	}
	if (str[ft_strlencher(str, '=') - 1] == '+' && ft_strchr(str, '=') != 0)
	{
		buffer1 = ft_content_plus(str);
		test_plus = 1;
	}
	else if (ft_strchr(str, '=') != 0)
		buffer1 = ft_content(str);
	else
		buffer1 = ft_strdup(str);
	ft_add_new(declare, str, buffer1, test_plus);
}

int	change_data(t_vars **env, char *str, int test_plus)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp;
	t_vars	*cur;

	cur = *env;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, str,
				ft_strlencher(cur->data, '=')) == 0 && test_plus == 1)
		{
			tmp1 = ft_strjoin(cur->data + ft_strlencher(cur->data, '=') + 1,
					str + ft_strlencher(str, '=') + 1);
			tmp2 = ft_substr(str, 0, ft_strlencher(str, '=') + 1);
			tmp = str;
			str = ft_strjoin(tmp2, tmp1);
			free(tmp);
			free(tmp2);
			free(tmp1);
			free(cur->data);
			cur->data = str;
			return (1);
		}
		else if (ft_strncmp(cur->data, str, ft_strlencher(cur->data, '=')) == 0)
		{
			free(cur->data);
			cur->data = ft_strdup(str);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

void	ft_modify_env(char *str, t_vars **env)
{
	t_vars	*cur;
	int		test_plus;

	test_plus = 0;
	cur = *env;
	if (ft_test_var(str, ft_strlencher(str, '=')) == 1)
		return ;
	if (str[ft_strlencher(str, '=') - 1] == '+')
	{
		str = ft_content_env(str);
		test_plus = 1;
	}
	if (change_data(env, str, test_plus) == 1)
		return ;
	add_envback(env, ft_envnew(ft_strdup(str)));
	if (test_plus == 1)
		free(str);
}
