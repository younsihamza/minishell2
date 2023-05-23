/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:59:04 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/23 18:01:52 by hyounsi          ###   ########.fr       */
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
