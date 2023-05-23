/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:24:20 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/23 14:35:24 by ichouare         ###   ########.fr       */
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

int	ft_buf(char **str)
{
	free(*str);
	return (1);
}

void	free_str(char **str1, char **str2)
{
	free(*str1);
	free(*str2);
}

int	ft_content_declare(char **data, char *str, char *buf, int test_plus)
{
	char	*trim1;
	char	*trim2;
	char	*tmp;

	if (ft_strncmp(*data, str,
			ft_strlencher(*data, '=')) == 0 && test_plus == 1)
	{
		if (ft_strchr(str, '=') == 0)
			return (ft_buf(&buf));
		trim1 = ft_strtrim(*data + 1 + ft_strlencher(*data, '='), "\"");
		trim2 = ft_strtrim(buf + 1 + ft_strlencher(*data, '='), "\"");
		tmp = trim1;
		trim1 = ft_strjoin(trim1, trim2);
		free_str(&tmp, &trim2);
		trim2 = ft_substr(buf, 0, ft_strlencher(buf, '=') + 1);
		free(buf);
		buf = ft_strjoin(trim2, trim1);
		free_str(&trim1, &trim2);
		trim2 = buf;
		buf = ft_content(buf);
		free_str(data, &trim2);
		*data = buf;
		return (1);
	}
	return (0);
}

void	ft_add_new(t_vars **declare, char *str, char *buffer1, int test_plus)
{
	t_vars	*cur;

	cur = *declare;
	while (cur != NULL)
	{
		if (ft_content_declare(&cur->data, str, buffer1, test_plus) == 1)
			return ;
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
