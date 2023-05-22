/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:08:59 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/22 16:29:23 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_first(int n)
{
	if (ft_isalpha(n) == 1)
		return (1);
	if (n == '_')
		return (1);
	return (0);
}

int	ft_test_var(char *str, int len)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0 || test_first(str[0]) == 0)
		return (1);
	while (i < len - 1)
	{
		if (ft_isalnum(str[i]) == 0)
			return (1);
		i++;
	}
	if (str[len - 1] == '+' && str[len] != '=')
		return (1);
	return (0);
}

int	ft_alpha_s(char str)
{
	int	i;

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

char	*ft_strtrim(char *s1, char *set)
{
	int		len;
	char	*p;
	int		i;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1) - 1;
	i = 0;
	while (ft_strchr(set, *(s1 + i)) != 0)
		i++;
	while (ft_strchr(set, *(s1 + len)) != 0)
		len-- ;
	if (len > i)
		p = ft_substr(s1, i, len - i + 1);
	else
		p = ft_substr(s1, i, - (len - i) + 1);
	return (p);
}
