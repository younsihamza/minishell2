/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:59:04 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/27 12:37:28 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_msg(char *var)
{
	write(1, "exit\n", 5);
	if (is_alpha(var) == -1)
	{
		write (1, "minishell: exit: too many arguments\n", 36);
		g_s[1] = 1;
		return (1);
	}
	write(1, "minishell: exit: numeric argument required\n", 43);
	g_s[1] = 255;
	return (2);
}

void	cmd_env(t_vars *env)
{
	while (env->data != NULL)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
}

void	ft_decremet_sh(t_vars **env, t_vars **declare)
{
	char	**tmp;
	char	*str;
	char	*buf;

	tmp = NULL;
	str = ft_itoa(ft_atoi(get_env_arr("SHLVL", *env) - 1));
	buf = ft_strjoin("export SHLVL=", str);
	tmp = ft_split(buf, ' ');
	ft_export(tmp, env, declare);
	free (str);
	free2d(tmp);
	free(tmp);
}

void	free2d(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
}
