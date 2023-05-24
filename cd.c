/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:12:51 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/24 14:09:18 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rn_der(char *p, t_data *d)
{
	int	a;
	int	b;

	d->pathhome = ft_calloc(1, 1024);
	if ((getcwd(d->pathhome, 1024)) == NULL)
	{
		free(d->pathhome);
		a = chdir(p);
		b = chdir(getcwd(d->pathhome, 1024));
		if (a == -1 && p != NULL)
		{
			g_s[1] = 1;
			printf("(%s) No such file or directory\n", p);
		}
		else if (ft_strcmp("..", p) == 0 && b == -1)
		{
			g_s[1] = 1;
			write(2, "cd: error retrieving current directory:", 39);
			write(2, "getcwd: cannot access parent directories", 40);
			write(2, ": No such file or directory\n", 28);
		}
		return (1);
	}
	return (0);
}

void	no_arg(t_data *d, t_vars **env, t_vars **declare)
{
	char	*buf;
	char	**tmp;

	tmp = NULL;
	if (chdir(get_env_arr("HOME", *env)) != -1)
	{
		if (get_env_arr("PWD",*env))
		{
			buf = ft_strjoin("export\nPWD=", get_env_arr("HOME", *env));
			tmp = ft_split(buf, '\n');
			free(buf);
			ft_export(tmp, env, declare);
			free2d(tmp);
			free(tmp);
			buf = ft_strjoin("export\nOLDPWD=", d->pathhome);
			tmp = ft_split(buf, '\n');
			ft_export(tmp, env, declare);
			free(buf);
			free(d->pathhome);
			free2d(tmp);
			free(tmp);
		}
	}
}

void	with_arg(t_data *d, t_vars **env, t_vars **declare)
{
	char	**tmp;
	char	*buf;

	tmp = NULL;
	if (get_env_arr("PWD",*env))
	{
		buf = ft_strjoin("export\nOLDPWD=", d->pathhome);
		tmp = ft_split(buf, '\n');
		ft_export(tmp, env, declare);
		free(buf);
		free(d->pathhome);
		free2d(tmp);
		free(tmp);
		d->pathhome = ft_calloc(1, 1024);
		getcwd(d->pathhome, 1024);
		buf = ft_strjoin("export\nPWD=", d->pathhome);
		tmp = ft_split(buf, '\n');
		free(buf);
		free(d->pathhome);
		ft_export(tmp, env, declare);
		free2d(tmp);
		free(tmp);
	}
}

void	cd_help(char *p, t_data *d, t_vars **env, t_vars **declare)
{
	int	a;

	if (ft_strcmp(p, "-") == 0)
	{
		a = chdir(get_env_arr("OLDPWD", *env));
		printf("%s\n", get_env_arr("OLDPWD", *env));
	}
	else
		a = chdir(p);
	if (a == -1)
	{
		g_s[1] = 1;
		printf("(%s) No such file or directory\n", p);
		free(d->pathhome);
	}
	else
		with_arg(d, env, declare);
}

void	cd(char *p, t_data *d, t_vars **env, t_vars **declare)
{
	if (rn_der(p, d) == 1)
		return ;
	if (p == NULL)
	{
		if (get_env_arr("HOME", *env) != NULL)
			no_arg(d, env, declare);
		else
		{
			g_s[1] = 1;
			write(2, "minishell: cd: HOME not set\n", 28);
		}
		return ;
	}
	cd_help(p, d, env, declare);
}
