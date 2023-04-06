/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:35:30 by hyounsi           #+#    #+#             */
/*   Updated: 2023/04/03 10:00:27 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		s_len ;
	char	*p;

	i = 0;
	s_len = ft_strlen(s);
	p = malloc(sizeof(char) * s_len + 1);
	if (!p)
		exit(0);
	while (*(s + i))
	{
		*(p + i) = *(s + i);
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
