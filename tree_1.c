/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:46:22 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/14 19:43:45 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_sone(t_lexer *lex, char *text, t_node **list)
{
	
	if (text[lex->i] == '$')
	{
		lex->j = lex->i + 1;
		while (ft_strchr(" =/$", text[lex->j]) == 0 && text[lex->j])
				lex->j++;
		if (lex->j != lex->i + 1)
			add_back(list, ft_lstnew(ft_substr(text,
						lex->i, lex->j - lex->i), "OP_VR", lex->spaces));
		else
			add_back(list, ft_lstnew(ft_substr(text,
						lex->i, 1), "OP_WR", lex->spaces));
		lex->i = lex->j;
		lex->spaces = 0;
	}
}

t_node	*simpletoken(char *text)
{
	t_lexer	lex;
	t_node	*list;

	list = NULL;
	lex.i = 0;
	lex.j = 0;
	while(text[lex.i])
	{
	if (text[lex.i] == '$')
	{
		lex.j = lex.i + 1;
		if(text[lex.j] >= '0' && text[lex.j] <= '9')
			{
				add_back(&list, ft_lstnew(ft_substr(text,
					lex.i, 2), "OP_VR", lex.spaces));
				lex.spaces = 0;
				lex.i +=2;
			}
		else
		{
			lex.j = lex.i + 1;
			if(text[lex.j] == '_' || (text[lex.j] >= 'a' && text[lex.j] <= 'z') || (text[lex.j] >= 'A' && text[lex.j] <= 'Z') )
			{
				lex.j++;
				while (ft_alpha_s(text[lex.j]) != -1 && text[lex.j])
					lex.j++;
				if (lex.j != lex.i + 1)
				{
					add_back(&list, ft_lstnew(ft_substr(text,
						lex.i, lex.j - lex.i), "OP_VR", lex.spaces));
				}
			}
			else
			{
				while (ft_strchr(" |><$\"", text[lex.j]) == 0 
					&& text[lex.j])
						lex.j++;
					add_back(&list, ft_lstnew(ft_substr(text,
							lex.i, lex.j - lex.i), "OP_WR", lex.spaces));
			}
			lex.i = lex.j;
			lex.spaces = 0;
	}
	}
	else
	{
		puts("here");
		lex.j = lex.i + 1;
		while(text[lex.j] && text[lex.j] != '$')
			lex.j++;
		add_back(&list, ft_lstnew(ft_substr(text,
						lex.i, lex.j - lex.i), "OP_WR", lex.spaces));
		lex.i = lex.j;
		lex.spaces = 0;
	}
	}
	return (list);
}

void	expand_one(char **data, char *tmp, t_vars *env)
{
	if(data[0][1] == '?')
		tmp = ft_strjoin(ft_itoa(g_s[1]), data[0] + 2);
	else
		tmp = get_env_arr(*data + 1, env);
	free(*data);
	if (tmp != NULL)
		*data = ft_strdup(tmp);
	else
		*data = ft_calloc(sizeof(char), 2);
}

t_node	*expand_two(char **data, t_node **str, t_vars *env)
{
	t_node	*str1;
	char	*tmp;

	tmp = NULL;
	str1 = simpletoken(*data);
	*str = str1;
	while (str1 != NULL)
	{
		if (ft_strcmp(str1->type, "OP_VR") == 0)
			expand_one(&str1->data, tmp, env);
		str1 = str1->next;
	}
	return (*str);
}

void	join_data(char **data, char *tmp, char **tokn)
{
	tmp = *tokn;
	*tokn = ft_strjoin(*tokn, *data);
	free(tmp);
	free(*data);
}
