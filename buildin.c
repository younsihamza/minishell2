/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:27:54 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/21 16:05:58 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **str, t_vars **env, t_vars **declare)
{
	int	i;

	// i = 0;
	// while(str[i])
	// {
	// 	printf("%s\n",str[i++]);
	// }
	i =1;
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

void	cd(char *p, t_data *d,t_vars **env,t_vars **declare)
{
	
	int	a;
	int b =0;
	char **tmp = NULL;
	char *buf;
	d->pathhome =ft_calloc(1,1024);
	if((getcwd(d->pathhome,1024)) == NULL)
	{
		free(d->pathhome);
		a = chdir(p);
		b =chdir(getcwd(d->pathhome,1024));
		if(a == -1 && p != NULL)
		{
			g_s[1]= 1;
			printf("(%s) No such file or directory\n", p);
		}
		else if(ft_strcmp("..",p) == 0 &&  b == -1)
		{
			g_s[1]= 1;
			write(2,"cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",108);
		}
		return;
	}
	if (p == NULL)
	{
		if(get_env_arr("HOME",*env) != NULL)
		{
			if(chdir(get_env_arr("HOME",*env)) != -1)
			{
				if(get_env_arr("PWD",*env))
				{
					buf = ft_strjoin("export\nPWD=",get_env_arr("HOME",*env));
					tmp = ft_split(buf, '\n');
					free(buf);
					ft_export(tmp, env, declare);
					free2d(tmp);
					free(tmp);
					buf = ft_strjoin("export\nOLDPWD=",d->pathhome);
					tmp = ft_split(buf, '\n');
					ft_export(tmp, env, declare);
					free(buf);
					free(d->pathhome);
					free2d(tmp);
					free(tmp);
				}
			}
		}
		else
		{
			g_s[1] =  1;
			write(2,"minishell: cd: HOME not set\n",23);
		}

		return ;
	}
	if(ft_strcmp(p,"-") == 0)
	{
		a = chdir(get_env_arr("OLDPWD",*env));
		printf("%s\n",get_env_arr("OLDPWD",*env));
	}
	else
		a = chdir(p);
	if (a == -1)
	{
		g_s[1] =  1;
		printf("(%s) No such file or directory\n", p);
	}else{
			if(get_env_arr("PWD",*env))
			{
				buf = ft_strjoin("export\nOLDPWD=",d->pathhome);
				tmp = ft_split(buf, '\n');
				ft_export(tmp, env, declare);
				free(buf);
				free(d->pathhome);
				free2d(tmp);
				free(tmp);
				d->pathhome =ft_calloc(1,1024);
				if(getcwd(d->pathhome,1024)== NULL)
					exit(0);
				buf = ft_strjoin("export\nPWD=",d->pathhome);
				tmp = ft_split(buf, '\n');
				free(buf);
				free(d->pathhome);
				ft_export(tmp, env, declare);
				free2d(tmp);
				free(tmp);
			}
	}
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
