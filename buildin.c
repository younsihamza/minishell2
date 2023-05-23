/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:27:54 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/23 18:18:41 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **var, t_vars **env, t_vars **declare)
{
	int		i;
	char	**tmp;
	char	*str;
	char	*buf;
	int 	status; 

	status = 0;
	i = 0;
	while (var[i])
		i++;
	if (i > 2)
	{
		status = ft_msg(var[1]);
		if (status  == 1)
			return ;
	}
	else
	{
		write (1, "exit\n", 5);
		if (var[1] && is_alpha(var[1]) == 1)
			write(1, "minishell: exit: numeric argument required\n", 43);	
	}
	tmp = NULL;
	str = ft_itoa(ft_atoi(get_env_arr("SHLVL", *env) - 1));
	buf = ft_strjoin("export SHLVL=", str);
	tmp = ft_split(buf, ' ');
	ft_export(tmp, env, declare);
	free(str);
	free2d(tmp);
	free(tmp);
	if(status == 2)
		exit(255);
	else  if(var[1] != NULL)
		exit(ft_atoi(var[1]));
	exit(0);
}

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

void	echo_help(t_help_var *v, char **cmd)
{
	v->i = 1;
	v->j = 1;
	v->newline = 0;
	v->len = 0;
	while (cmd[v->i] != NULL)
	{
		if (cmd[v->i][0] == '-')
		{
			v->j = 1;
			while (cmd[v->i][v->j])
			{
				if (cmd[v->i][v->j] != 'n')
					v->len = 1;
				v->j++;
			}	
		}
		else
			v->len = 1;
		if (v->len == 0 && v->j != 1)
			v->newline = v->i++;
		else
			break ;
	}
}

void	echo(char **cmd)
{
	t_help_var	v;

	echo_help(&v, cmd);
	while (cmd[v.i])
	{
		printf("%s", cmd[v.i]);
		v.i++;
		if (cmd[v.i] != NULL)
			printf(" ");
	}
	if (v.newline == 0)
		printf("\n");
}
