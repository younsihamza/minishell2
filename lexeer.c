#include "minishell.h"


void  token_one(t_lexer *lex, char *text, t_node **head)
{
    if(text[lex->i] == 39)
        {
            lex->j = lex->i + 1;
            while(text[lex->j] != 39 && text[lex->j])
                lex->j++;
            add_back(head,ft_lstnew(ft_substr(text,lex->i + 1,lex->j -lex->i - 1),"SINGLE",lex->spaces));
            lex->i = lex->j + 1;
            lex->spaces = 0;
        }
        if(text[lex->i] == '<')
        {
            lex->j  = lex->i;
            if(text[lex->j+1] == '<')
                lex->j+=2;
            else
                lex->j++;
                if(lex->j != lex->i)
                {
                    add_back(head,ft_lstnew(ft_substr(text, lex->i, lex->j-lex->i),"OP_FILE",lex->spaces));
                    lex->i = lex->j;
                }
                 lex->spaces = 0;
        }
        if(text[lex->i] == '|')
        { 
                add_back(head,ft_lstnew(ft_substr(text, lex->i, 1),"OP_PIPE",lex->spaces));
                lex->i++;
                lex->spaces = 0;
        }
}


void  token_two(t_lexer *lex, char *text, t_node **head)
{
if(text[lex->i] == '>')
        {
            lex->j = lex->i;
            if(text[lex->i+1] == '>')
            {
                lex->j += 2;
            }else
                lex->j++;
                if(lex->j != lex->i)
                {
                    add_back(head,ft_lstnew(ft_substr(text, lex->i, lex->j-lex->i),"OP_FILE",lex->spaces));
                    lex->i = lex->j ;
                }
                lex->spaces = 0;
        }
        if(text[lex->i] == '$')
        {
            lex->j = lex->i + 1;
            while(ft_strchr(" |><$\"",text[lex->j]) == 0 && text[lex->j])
                    lex->j++;
            if(lex->j != lex->i +1)
                add_back(head,ft_lstnew(ft_substr(text,lex->i ,lex->j-lex->i),"OP_VR",lex->spaces));
            else
                add_back(head,ft_lstnew(ft_substr(text,lex->i ,1),"OP_WR",lex->spaces));
            lex->i = lex->j;
            lex->spaces = 0;
        }
}
t_node *token(char *text)
{
    char *p = " |><$\"";
    t_node *head;
    t_lexer lex;
    lex.spaces = 0;
    t_node *ptr;
    head = NULL;
    lex.i = 0;
    lex.j = 0;
    while(text[lex.i])
    {
        if(text[ lex.i] == 34)
        {
            lex.j =  lex.i + 1;
            while(text[lex.j] != 34 && text[lex.j])
                lex.j++;
            add_back(&head, ft_lstnew(ft_substr(text,lex.i + 1, lex.j - lex.i - 1), "DOUBLE", lex.spaces));
             lex.i = lex.j + 1;
            lex.spaces = 0;
        }
        token_one(&lex, text, &head);
        token_two(&lex, text, &head);
        if(ft_strchr(p,text[lex.i]) == 0)
        {
            lex.j = lex.i;
            while(text[lex.i] != ' ' && ft_strchr(p,text[lex.j]) == 0 && text[lex.j])
                lex.j++;
            if(lex.j != lex.i)
            {
                add_back(&head,ft_lstnew(ft_substr(text, lex.i, lex.j - lex.i),"OP_WR",lex.spaces));
                lex.i = lex.j;
            }
            lex.spaces = 0;
        }
        while(text[lex.i] == ' ' && text[lex.i])
        {
            lex.spaces = 1;
            lex.i++;
        }
    }
    ptr = head;
    lex.i= 1;
    while(ptr != NULL)
    {
        ptr->i = lex.i;
        lex.i++;
        ptr = ptr->next;
    }
    free(text);
    return(head);
}