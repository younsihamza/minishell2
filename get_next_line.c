/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:21:40 by hyounsi           #+#    #+#             */
/*   Updated: 2023/05/20 19:00:15 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchrs( char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (*str != (char)c)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}

void	help_1(char **s, char **p, int a)
{
	char	*tmp;

	if (!*s && a != 0)
	{
		*s = ft_substr(*p, 0, ft_strlens(*p, '\0') + 1);
		ft_bzero(*p, ft_strlens(*p, '\0'));
	}
	else if (a != 0)
	{
		tmp = *s;
		*s = ft_strjoin(*s, *p);
		free(tmp);
		ft_bzero(*p, ft_strlens(*p, '\0'));
	}
}

char	*help_fn(char **s, char **p)
{
	char	*line;
	char	*tmp;

	if (ft_strlens(*s, '\0') == 0)
	{
		free(*s);
		free(*p);
		return (NULL);
	}
	if (ft_strchrs(*s, '\n'))
	{
		line = ft_substr(*s, 0, ft_strlens(*s, '\n'));
		tmp = *s;
		*s = ft_substr(*s, ft_strlens(*s, '\n') + 1, ft_strlens(*s, '\0') + 1);
		free(tmp);
	}
	else
	{
		tmp = *s;
		line = ft_substr(*s, 0, ft_strlens(*s, '\0') );
		free(tmp);
		*s = NULL;
	}
	free(*p);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*p;
	static char		*s;
	char			*line;
	int				a;

	a = 3;
	if (fd < 0 || 1 <= 0)
		return (NULL);
	p = (char *)ft_calloc(sizeof(char), 1 + 1);
	if (!p)
		return (NULL);
	while (ft_strchrs(s, '\n') == NULL && a)
	{
		a = read(fd, p, 1);
		if (a < 0)
		{
			free(p);
			return (NULL);
		}
		help_1(&s, &p, a);
	}
	line = help_fn(&s, &p);
	return (line);
}
