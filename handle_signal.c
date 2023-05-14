/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:25:37 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/14 15:09:43 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	
	if (sig == SIGINT && g_s[0] == 0)
	{
		fprintf(stderr, "%d\n",sig);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT && g_s[0] == 1)
		write (1, "\n", 1);
	else if (sig == SIGQUIT && g_s[0] == 1)
		write (1, "Quit\n", 5);
}
