/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:25:37 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/21 16:05:05 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	g_s[2] = 1;

	if (sig == SIGINT && g_s[0] == 1)
	{
		g_s[1] = 2;
	}
	else if (sig == SIGINT)
	{
		g_s[1] = 2;
		write (2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT && g_s[0] == 1)
	{
		g_s[1] = 3;
	}
}


void handle_new(int sig)
{	
	
	g_s[2] = 1;
	if(sig == SIGINT)
	{ 
		if(g_s[0] == 0)
			handle_sigint(SIGINT);
		g_s[1] = 2;
		return;
	}
	if(sig == SIGQUIT)
	{ 
		g_s[1] = 3;
		return;
	}
}