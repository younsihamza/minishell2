/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:29:28 by ichouare          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/13 16:50:23 by hyounsi          ###   ########.fr       */
=======
/*   Updated: 2023/05/13 13:21:55 by ichouare         ###   ########.fr       */
>>>>>>> d72b434c1be88131493498da183cf6412bf69442
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
<<<<<<< HEAD
	t_vars	*newlist;
	t_vars *hold;
	t_vars *tmp;

	cur = (*vars);
	hold = NULL;
	newlist = NULL;
=======
	t_vars	*prev;

	cur = (*vars);
	prev = cur;

>>>>>>> d72b434c1be88131493498da183cf6412bf69442
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, args[*i],
				ft_strlencher(cur->data, '=')) != 0)
		{
<<<<<<< HEAD
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
=======
				prev = prev->next;
				puts(cur->data);
				// free(cur->data);
				//free(cur);
				cur = prev;
		}
		else
				cur = cur->next;
>>>>>>> d72b434c1be88131493498da183cf6412bf69442
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
	if ((ft_strlen(str) == 1 && str[0] == '=') || str[0] == '=' || ft_strlen(str) == 0)
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

void	ft_modify_env(char *str, t_vars **env)
{
	t_vars	*cur;

	cur = *env;
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
	add_envback(env, ft_envnew(ft_strdup (str)));
}
