/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:27:20 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/21 16:45:40 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlencher(char *str, int a)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != a && str[i])
		i++;
	return (i);
}

t_vars	*get_declare(char **env)
{
	int			i;
	t_vars		*vars;
	t_declare	declare;

	i = 0;
	vars = NULL;
	while (env[i])
	{
		declare.std1 = ft_substr(env[i], 0, ft_strlencher(env[i], '=') + 1);
		declare.std2 = ft_substr(env[i], ft_strlencher(env[i], '=') + 1,
				ft_strlen(env[i]));
		declare.content = ft_strjoin(declare.std1, "\"");
		declare.tmp = declare.content;
		declare.content = ft_strjoin(declare.content, declare.std2);
		free(declare.tmp);
		declare.tmp = declare.content;
		declare.content = ft_strjoin(declare.content, "\"");
		free(declare.tmp);
		free(declare.std2);
		free(declare.std1);
		add_envback(&vars, ft_envnew(declare.content));
		i++;
	}
	return (vars);
}
void free_env_declare(t_env *envir)
{
	t_vars *head = envir->envv;
	t_vars *tmp;
	while(head != NULL)
	{
		tmp = head;
		head=head->next;
		free(tmp->data);
		free(tmp);
	}
	head = envir->declare;
	while(head != NULL)
	{
		tmp = head;
		head=head->next;
		free(tmp->data);
		free(tmp);
	}
}
void	ft_shell(t_env *envir, char *pathHome)
{
	char	*text;
	t_tree	*root;
	t_node	*head;

	int original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
			return ;
	while (1)
	{
		g_s[3] = 1;
	signal (SIGINT, &handle_sigint);
	signal (SIGQUIT, &handle_sigint);
	if(ttyname(0) == NULL)
	{
		if (dup2(original_stdin, STDIN_FILENO) == -1) 
        	close(original_stdin);
	}
		text = readline ("minishell -> $> ");
		if (!text)
		{
			free_env_declare(envir);
			break;
		}
		if (*text)
			add_history(text);
		head = token(text);
		root = bulid_tree(head, envir, pathHome);
	}
}

int	main(int ac, char **argv, char **env)
{
	char	*pathhome;
	t_env	envir;
	g_s[0] = 0;
	g_s[1] = 0;
	rl_catch_signals = 0;
	envir.envv = NULL;
	envir.declare = NULL;
	if(*env == NULL|| get_env_arr("SHLVL", envir.envv) != NULL)
	{
		add_envback(&envir.declare, ft_envnew(ft_strdup ("SHLVL=1")));
		add_envback(&envir.envv, ft_envnew(ft_strdup ("SHLVL=1")));
	}
	else
	{
		envir.envv = get_env(env);
		envir.declare = get_declare(env);
		if(get_env_arr("SHLVL", envir.envv))
		{
			char **tmp = NULL;
			char *str = ft_itoa(ft_atoi(get_env_arr("SHLVL", envir.envv)) + 1);
			char *buf = ft_strjoin("export SHLVL=",str);
			tmp = ft_split(buf, ' ');
			free(buf);
			ft_export(tmp, &envir.envv, &envir.declare);
			free(str);
			free2d(tmp);
			free(tmp);
		}
	}
	pathhome = NULL;
	argv = NULL;
	if (ac != 1)
		return (1);
	ft_shell(&envir, pathhome);
}
