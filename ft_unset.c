/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:29:28 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/14 18:42:55 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void addback_r( t_vars** list , t_vars* new)
 {
     t_vars* hold;
     hold = *list;
     if(*list == NULL)
     {
        *list = new;
        return;
     }
        while(hold->next != NULL)
            hold = hold->next;
        hold->next = new;
        
 }
void	ft_remove(char **args, int *i, t_vars **vars)
{
	t_vars	*cur;
	t_vars	*newlist;
	t_vars *hold;
	t_vars *tmp;

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
			addback_r(&newlist,hold);
		}
		else
		{
			tmp = cur;
			cur = cur->next;
			if(tmp != NULL)
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
		if (is_alpha(args[i]) == -1)
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

void	ft_modify(char *str, t_vars **declare)
{
	char	*buffer1;

	buffer1 = NULL;
	if (ft_test_var(str,ft_strlencher(str,'=')) == 1)
	{
		g_s[1] = 1;
		printf("bash: export: `%s': not a valid identifier\n", str);
		return ;
	}
	if (ft_strchr(str, '=') != 0)
		buffer1 = ft_content(str);
	else
		buffer1 = ft_strdup(str);
	ft_add_new(declare, str, buffer1);
}

void	ft_modify_env(char *str, t_vars **env)
{
	t_vars	*cur;

	cur = *env;
	if (ft_test_var(str,ft_strlencher(str,'=')) == 1)
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
	add_envback(env, ft_envnew(ft_strdup (str)));
}
