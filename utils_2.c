/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:08:59 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/18 15:29:33 by ichouare         ###   ########.fr       */
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


int	ft_isalpha(int n)
{
	if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122))
		return (1);
	return (0);
}
int	ft_isdigit(int n)
{
	if (n >= 48 && n <= 57)
		return (1);
	return (0);
}

int	ft_isalnum(int n)
{
	if (ft_isalpha(n) == 1)
		return (1);
	if(n == '_')
		return (1);
	if (ft_isdigit(n) == 1)
		return (1);
	return (0);
}
int test_first(int n)
{
	if (ft_isalpha(n) == 1)
		return (1);
	if(n == '_')
		return (1);
	return(0);
}
int ft_test_var(char *str,int len)
{
	int i= 0;
	if(ft_strlen(str) == 0 || test_first(str[0]) == 0)
		return(1);
	while(i < len - 1)
	{
		if(ft_isalnum(str[i]) == 0)
			return(1);
		i++;	
	}
	if(str[len] != '=')
		return(1);
	return(0);
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
