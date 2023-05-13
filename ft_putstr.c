/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:09 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/13 17:52:08 by hyounsi          ###   ########.fr       */
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

static int	llm(char const *str, int i, int sin)
{
	int	j;
	int	result;

	j = 0;
	result = 0;
	while ((*(str + i) >= 48) && (*(str + i) <= 57))
	{
		result = result * 10;
		result += *(str + i) - '0';
		i++;
		if (j >= 19)
		{
			if (sin == -1)
				return (0);
			return (-1);
		}
		j++;
	}
	return (result * sin);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	result;

	result = 0;
	s = 1;
	i = 0;
	while ((*(str + i) == 32) || (*(str + i) >= 9 && *(str + i) <= 13))
		i++;
	if (*(str + i) == '-')
	{
		s = -1;
		i++;
	}
	else if (*(str + i) == '+')
		i++;
	return (llm(str, i, s));
}
