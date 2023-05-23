/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:46:22 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/23 17:08:52 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_sone(t_lexer *lex, char *text, t_node **list)
{	
	lex->j = lex->i + 1;
	if (text[lex->j] == '_' || (text[lex->j] >= 'a'
			&& text[lex->j] <= 'z') || (text[lex->j] >= 'A'
			&& text[lex->j] <= 'Z'))
	{
		lex->j++;
		while (ft_alpha_s(text[lex->j]) != -1 && text[lex->j])
			lex->j++;
		if (lex->j != lex->i + 1)
		{
			add_back(list, ft_lstnew(ft_substr(text,
						lex->i, lex->j - lex->i), "OP_VR", lex->spaces));
		}
	}
	else
	{
		while (ft_strchr(" '|><$\"", text[lex->j]) == 0
			&& text[lex->j])
				lex->j++;
		add_back(list, ft_lstnew(ft_substr(text,
					lex->i, lex->j - lex->i), "OP_WR", lex->spaces));
	}
	lex->i = lex->j;
	lex->spaces = 0;
}

void	part_one(t_lexer *lex, char *text, t_node **list)
{
	lex->j = lex->i + 1;
	if ((text[lex->j] >= '0' && text[lex->j] <= '9')
		|| text[lex->j] == '?')
	{
		add_back(list, ft_lstnew(ft_substr(text,
					lex->i, 2), "OP_VR", lex->spaces));
		lex->spaces = 0;
		lex->i += 2;
	}
	else
		token_sone(lex, text, list);
}

t_node	*simpletoken(char *text)
{
	t_lexer	lex;
	t_node	*list;

	list = NULL;
	lex.i = 0;
	lex.j = 0;
	while (text[lex.i])
	{
		if (text[lex.i] == '$')
			part_one(&lex, text, &list);
		else
		{
			lex.j = lex.i + 1;
			while (text[lex.j] && text[lex.j] != '$')
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
	char	*number;
	char	*tmp2;

	tmp2 = NULL;
	if (data[0][1] == '?')
	{
		number = ft_itoa(g_s[1]);
		tmp = ft_strjoin(number, data[0] + 2);
		tmp2 = tmp;
		free(number);
	}
	else
		tmp = get_env_arr(*data + 1, env);
	free (*data);
	if (tmp != NULL)
		*data = ft_strdup(tmp);
	else
		*data = ft_calloc(sizeof(char), 2);
	if(tmp2 != NULL)
		free(tmp2);
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
