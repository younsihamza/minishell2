/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:16:44 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/20 18:56:18 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*p;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		*(p + i) = '\0';
		i++;
	}
}



size_t	ft_strlens(char *p, char a)
{
	size_t	i;

	i = 0;
	if (!p)
		return (0);
	while (*(p + i) != a)
		i++;
	return (i);
}

