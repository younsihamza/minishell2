/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:27:20 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/11 16:41:16 by ichouare         ###   ########.fr       */
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

void	ft_shell(t_vars *env, t_vars *declare, char *pathHome)
{
	char	*text;
	t_tree	*root;
	t_node	*head;

	while (1)
	{
		text = readline ("minishell -> $> ");
		if (!text)
			break ;
		if (*text)
			add_history(text);
		head = token(text);
		root = bulid_tree(head, env, declare, pathHome);
	}
}

int	main(int ac, char **argv, char **env)
{
	t_vars	*list;
	char	*pathhome;
	t_vars	*declare;

	g_s = 0;
	rl_catch_signals = 0;
	signal (SIGINT, &handle_sigint);
	signal (SIGQUIT, &handle_sigint);
	list = get_env(env);
	declare = get_declare(env);
	pathhome = get_env_arr("ZDOTDIR", list);
	argv = NULL;
	if (ac != 1)
		return (1);
	ft_shell(list, declare, pathhome);
}
