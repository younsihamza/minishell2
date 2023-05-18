/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:24:20 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/18 15:49:17 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_content(char *str)
{
	char	*tmp;
	char	*buffer1;
	char	*buffer2;

	tmp = NULL;
	buffer1 = NULL;
	buffer2 = NULL;
	buffer1 = ft_substr(str, 0, ft_strlencher(str, '=') + 1);
	buffer2 = ft_substr(str, ft_strlencher(str, '=') + 1, ft_strlen(str));
	tmp = buffer2;
	buffer2 = ft_strjoin("\"", buffer2);
	free(tmp);
	tmp = buffer2;
	buffer2 = ft_strjoin(buffer2, "\"");
	free(tmp);
	tmp = buffer1;
	buffer1 = ft_strjoin(buffer1, buffer2);
	free(buffer2);
	free(tmp);
	return (buffer1);
}

void	ft_add_new_up(t_vars **declare, char *str, char *buffer1, char *data)
{
	t_vars	*cur;
	char *tmp;

	cur = *declare;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, str, ft_strlencher(cur->data, '=')) == 0)
		{
			if (ft_strchr(str, '=') == 0)
			{
				free(buffer1);
				return ;
			}
			tmp = cur->data;
			cur->data = ft_strjoin(ft_substr(cur->data, 0, ft_strlen(cur->data)), data);
			free(tmp);
			return ;
		}
	cur = cur->next;
	}
	add_envback(declare, ft_envnew(buffer1));
}
void	ft_add_new(t_vars **declare, char *str, char *buffer1)
{
	t_vars	*cur;

	cur = *declare;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, str, ft_strlencher(cur->data, '=')) == 0)
		{
			if (ft_strchr(str, '=') == 0)
			{
				free(buffer1);
				return ;
			}
			free(cur->data);
			cur->data = buffer1;
			return ;
		}
	cur = cur->next;
	}
	add_envback(declare, ft_envnew(buffer1));
}
