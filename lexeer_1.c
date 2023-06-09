/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:14:33 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/13 15:19:56 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_last(t_lexer *lex, char *text, t_node **head)
{
	char	*p;

	p = " |><$\"";
	if (ft_strchr(p, text[lex->i]) == 0)
	{
		lex->j = lex->i;
		while (text[lex->i] != ' '
			&& ft_strchr(p, text[lex->j]) == 0 && text[lex->j])
			lex->j++;
		if (lex->j != lex->i)
		{
			add_back(head, ft_lstnew(ft_substr(text,
						lex->i, lex->j - lex->i), "OP_WR", lex->spaces));
			lex->i = lex->j;
		}
		lex->spaces = 0;
	}
}

void	add_id(t_node *head)
{
	t_node	*ptr;
	int		i;

	ptr = head;
	i = 1;
	while (ptr != NULL)
	{
		ptr->i = i;
		i++;
		ptr = ptr->next;
	}
}

int	check_error(int i, char *text, t_node **head)
{
	if (text[i] == '\0')
	{
		g_s[1]= write(2, "error syntax \n", 15);
		free_head(*head);
		free(text);
		return (1);
	}
	return (0);
}
