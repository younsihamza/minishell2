/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:27:54 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/13 16:28:08 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **str, t_vars **env, t_vars **declare)
{
	int	i;

	i = 1;
	if (!str[i])
	{
		while (*declare != NULL)
		{
			printf("%s\t", "declare -x");
			printf("%s\n", (*declare)->data);
			*declare = (*declare)->next;
		}
	}
	while (str[i])
	{
		ft_modify(str[i], declare);
		if (ft_strchr(str[i], '=') != 0)
			ft_modify_env(str[i], env);
		i++;
	}
}

void	echo(char **cmd)
{
	int	i;
	int	newline;
	int j = 1;
	int cs = 0;

	i = 1;
	newline = 0;
	cs = 0;
	while(cmd[i] != NULL)
	{
		if(cmd[i][0]=='-')
		{
			j = 1;
			while(cmd[i][j])
			{
				if(cmd[i][j] != 'n')
					cs = 1;
				j++;
			}	
		}
		else
			cs = 1;
		if(cs == 0 && j != 1)
			newline = i++;
		else 
			break;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i] != NULL)
			printf(" ");
	}
	if (newline == 0)
		printf("\n");
}

void	cd(char *p, t_data *d)
{
	int	a;

	if (p == NULL)
	{
		chdir(d->pathhome);
		return ;
	}
	a = chdir(p);
	if (a == -1)
		g_s[1] = printf("(%s) No such file or directory\n", p);
}

void	cmd_env(t_vars *env)
{
	while (env->data != NULL)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
}

char	**ft_env(t_vars *vars)
{
	t_vars	*tmp;
	char	**ourenv;
	int		i;

	tmp = vars;
	i = 0;
	while (vars != NULL)
	{
		i++;
		vars = vars->next;
	}
	ourenv = ft_calloc(sizeof(char *), i + 1);
	if (!ourenv)
		exit(0);
	i = 0;
	while (tmp != NULL)
	{
		ourenv[i] = tmp->data;
		i++;
		tmp = tmp->next;
	}
	return (ourenv);
}
