/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:49:18 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/13 12:04:36 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delimet(char *l)
{
	int	i;

	i = 0;
	while (ft_strchr(" <>", l[i]) != 0)
		i++;
	return (l + i);
}

void	ft_close(int **fd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	build_in_child(char **cmd, t_vars **env, t_vars **declare)
{
	char	*path;

	if (ft_strcmp("echo", cmd[0]) == 0)
		echo(cmd);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
	{
		path = ft_calloc(sizeof(char), 1024);
		if (!path)
			exit(0);
		if (getcwd(path, 1024) != NULL)
			printf("%s\n", path);
		else
			printf("%s", "error");
		free(path);
	}
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd, env, declare);
	else if (ft_strcmp(cmd[0], "env") == 0)
		cmd_env(*env);
	exit(0);
}

void	help_free(t_help_var *v, char **cmd)
{
	write(2, "IH : command not found\n", 24);
	free2d(cmd);
	free(v->envs);
	free(v->split_path);
}

void	cmd1(char **cmd, t_vars **env, t_vars **declare)
{
	t_help_var	v;

	v.i = 0;
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "pwd") == 0
		|| ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "env") == 0)
		build_in_child(cmd, env, declare);
	v.envs = ft_env(*env);
	execve(cmd[0], cmd, v.envs);
	v.path = get_env_arr("PATH", *env);
	v.split_path = ft_split(v.path, ':');
	if (v.split_path != NULL)
	{
		while (v.split_path[v.i])
		{
			v.tmp = ft_strjoin(v.split_path[v.i], "/");
			v.joincmd = ft_strjoin(v.tmp, cmd[0]);
			free(v.tmp);
			execve(v.joincmd, cmd, v.envs);
			free(v.joincmd);
			v.i++;
		}
		free2d(v.split_path);
	}
	help_free(&v, cmd);
}
