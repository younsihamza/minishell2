/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:58:29 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/11 13:17:30 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_one(t_lexer *lex, char *text, t_node **head)
{
	if (text[lex->i] == 34)
	{
		lex->j = lex->i + 1;
		while (text[lex->j] != 34 && text[lex->j])
			lex->j++;
		add_back(head, ft_lstnew(ft_substr(text,
					lex->i + 1, lex->j - lex->i - 1), "DOUBLE", lex->spaces));
			lex->i = lex->j + 1;
		lex->spaces = 0;
	}
	if (text[lex->i] == 39)
	{
		lex->j = lex->i + 1;
		while (text[lex->j] != 39 && text[lex->j])
			lex->j++;
		add_back(head, ft_lstnew(ft_substr(text,
					lex->i + 1, lex->j - lex->i - 1), "SINGLE", lex->spaces));
		lex->i = lex->j + 1;
		lex->spaces = 0;
	}
}

void	token_two(t_lexer *lex, char *text, t_node **head)
{
	if (text[lex->i] == '<')
	{
		lex->j = lex->i;
		if (text[lex->j + 1] == '<')
			lex->j += 2;
		else
			lex->j++;
		if (lex->j != lex->i)
		{
			add_back(head, ft_lstnew(ft_substr(text,
						lex->i, lex->j - lex->i), "OP_FILE", lex->spaces));
			lex->i = lex->j;
		}
		lex->spaces = 0;
	}
	if (text[lex->i] == '|')
	{
		add_back(head, ft_lstnew(ft_substr(text,
					lex->i, 1), "OP_PIPE", lex->spaces));
		lex->i++;
		lex->spaces = 0;
	}
}

void	token_tree(t_lexer *lex, char *text, t_node **head)
{
	if (text[lex->i] == '>')
	{
		lex->j = lex->i;
		if (text[lex->i + 1] == '>')
			lex->j += 2;
		else
			lex->j++;
		if (lex->j != lex->i)
		{
			add_back(head, ft_lstnew(ft_substr(text, lex->i,
						lex->j - lex->i), "OP_FILE", lex->spaces));
			lex->i = lex->j ;
		}
		lex->spaces = 0;
	}
}

void	token_foor(t_lexer *lex, char *text, t_node **head)
{
	if (text[lex->i] == '$')
	{
		lex->j = lex->i + 1;
		while (ft_strchr(" |><$\"", text[lex->j]) == 0 && text[lex->j])
				lex->j++;
		if (lex->j != lex->i +1)
			add_back(head, ft_lstnew(ft_substr(text,
						lex->i, lex->j - lex->i), "OP_VR", lex->spaces));
		else
			add_back(head, ft_lstnew(ft_substr(text,
						lex->i, 1), "OP_WR", lex->spaces));
		lex->i = lex->j;
		lex->spaces = 0;
	}	
}

t_node	*token(char *text)
{
	t_node	*head;
	t_lexer	lex;

	lex.spaces = 0;
	head = NULL;
	lex.i = 0;
	lex.j = 0;
	while (text[lex.i])
	{
		token_one(&lex, text, &head);
		token_two(&lex, text, &head);
		token_tree(&lex, text, &head);
		token_foor(&lex, text, &head);
		token_last(&lex, text, &head);
		while (text[lex.i] == ' ' && text[lex.i])
		{
			lex.spaces = 1;
			lex.i++;
		}
	}
	add_id(head);
	free(text);
	return (head);
}
