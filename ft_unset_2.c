/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:21:48 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/24 15:50:58 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove(char **args, int *i, t_vars **vars)
{
	t_vars	*dummy;
	t_vars	*cur;
	t_vars	*tmp;

	dummy = malloc (sizeof(t_vars) * 1);
	dummy->next = *vars;
	cur = dummy;
	while (cur->next != NULL)
	{
		if (ft_strncmp(cur->next->data, args[*i],
				ft_strlencher(cur->next->data, '=')) == 0)
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp->data);
			free(tmp);
		}
		else
			cur = cur->next;
	}
	*vars = dummy->next;
	free (dummy);
}

char	*ft_content_plus(char *str)
{
	char	*tmp;
	char	*buffer1;
	char	*buffer2;

	tmp = NULL;
	buffer1 = NULL;
	buffer2 = NULL;
	buffer1 = ft_substr(str, 0, ft_strlencher(str, '=') - 1);
	tmp = buffer1;
	buffer1 = ft_strjoin(buffer1, "=");
	free(tmp);
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

char	*ft_content_env(char *str)
{
	char	*tmp;
	char	*buffer1;
	char	*buffer2;

	tmp = NULL;
	buffer1 = NULL;
	buffer2 = NULL;
	buffer1 = ft_substr(str, 0, ft_strlencher(str, '=') - 1);
	tmp = buffer1;
	buffer1 = ft_strjoin(buffer1, "=");
	free(tmp);
	buffer2 = ft_substr(str, ft_strlencher(str, '=') + 1, ft_strlen(str));
	tmp = buffer1;
	buffer1 = ft_strjoin(buffer1, buffer2);
	free(buffer2);
	free(tmp);
	return (buffer1);
}

int	handle_content(char **data, char *str)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp;

	tmp1 = ft_strjoin(*data + ft_strlencher(*data, '=') + 1,
			str + ft_strlencher(str, '=') + 1);
	tmp2 = ft_substr(str, 0, ft_strlencher(str, '=') + 1);
	tmp = str;
	str = ft_strjoin(tmp2, tmp1);
	free(tmp);
	free(tmp2);
	free(tmp1);
	free(*data);
	*data = str;
	return (1);
}
