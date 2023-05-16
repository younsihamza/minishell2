/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:25:37 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/16 13:33:10 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	g_s[2] = 1;
	if (sig == SIGINT && g_s[0] == 0)
	{
		g_s[1] = 2;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT && g_s[0] == 1)
	{
		write (1, "\n", 1);
		g_s[1] = 2;
	}
	else if (sig == SIGQUIT && g_s[0] == 1)
	{
		write (1, "Quit\n", 5);
		g_s[1] = 3;
	}
}
