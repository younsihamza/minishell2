/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:08:59 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/14 18:10:32 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z'))
			i++;
		else
			return (-1);
	}
	return (i);
}


int ft_alpha_s(char str)
{
	int i;
	i = 0;
	if ((str >= 'a' && str <= 'z')
		|| (str >= 'A' && str <= 'Z')
		|| str == '_'
		|| (str >= '0' && str <= '9'))
		i++;
	else
		return (-1);
	return (i);
}