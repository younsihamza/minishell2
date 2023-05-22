/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:24:20 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/22 18:46:47 by ichouare         ###   ########.fr       */
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

void	ft_add_new(t_vars **declare, char *str, char *buffer1, int test_plus)
{
	t_vars	*cur;
	char	*trim1;
	char	*trim2;
	char	*tmp;

	cur = *declare;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->data, str,
				ft_strlencher(cur->data, '=')) == 0 && test_plus == 1)
		{
			if (ft_strchr(str, '=') == 0)
			{
				free(buffer1);
				return ;
			}
			trim1 = ft_strtrim(cur->data + 1
					+ ft_strlencher(cur->data, '='), "\"");
			trim2 = ft_strtrim(buffer1 + 1
					+ ft_strlencher(cur->data, '='), "\"");
			tmp = trim1;
			trim1 = ft_strjoin(trim1, trim2);
			free(tmp);
			free(trim2);
			trim2 = ft_substr(buffer1, 0, ft_strlencher(buffer1, '=') + 1);
			free(buffer1);
			buffer1 = ft_strjoin(trim2, trim1);
			free(trim1);
			free(trim2);
			trim2 = buffer1;
			buffer1 = ft_content(buffer1);
			free(cur->data);
			free(trim2);
			cur->data = buffer1;
			return ;
		}
		else if (ft_strncmp(cur->data, str, ft_strlencher(cur->data, '=')) == 0)
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
