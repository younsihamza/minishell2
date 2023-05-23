/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:13:58 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/23 15:02:07 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shlevel(t_env *envir)
{
	char		**tmp;
	char		*str;
	char		*buf;

	tmp = NULL;
	str = ft_itoa(ft_atoi(get_env_arr("SHLVL", envir->envv)) + 1);
	buf = ft_strjoin("export SHLVL=", str);
	tmp = ft_split(buf, ' ');
	free(buf);
	ft_export(tmp, &envir->envv, &envir->declare);
	free(str);
	free2d(tmp);
	free(tmp);
}

void	add_attribute(t_vars **env, t_vars **declare)
{
	add_envback(env, ft_envnew(ft_strdup ("TERM=xterm-256color")));
	add_envback(declare, ft_envnew(ft_strdup ("SHLVL=1")));
	add_envback(env, ft_envnew(ft_strdup ("SHLVL=1")));
}

void	shell_exit(t_env *envir)
{
	write(1, "exit\n", 5);
	free_env_declare(envir);
	exit(0);
}

void	join_data(char **data, char *tmp, char **tokn)
{
	tmp = *tokn;
	*tokn = ft_strjoin(*tokn, *data);
	free(tmp);
	free(*data);
}
