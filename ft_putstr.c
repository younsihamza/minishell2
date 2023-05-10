/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:09 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/10 12:21:02 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	write(fd, "\n", 1);
}

char	*herdoc_expand(char *data, t_vars *env)
{
	t_node	*str;
	t_node	*ptr;
	t_node	*ss;
	char	*last_data;

	str = NULL;
	ptr = NULL;
	last_data = ft_calloc(1, 1);
	ptr = expand_two(&data, &ss, env);
	free(data);
	while (ptr != NULL)
	{
		if (ptr->data != NULL)
			join_data(&ptr->data, NULL, &last_data);
		str = ptr;
		ptr = ptr->next;
		free(str);
	}
	return (last_data);
}
