/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:14:03 by ichouare          #+#    #+#             */
/*   Updated: 2023/03/30 18:28:19 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


t_vars  *ft_unset(char **args, t_vars **vars)
{
    t_vars *cur = NULL;
    t_vars *prev = NULL;
    t_vars *list = NULL;
    
    cur = *vars;
    list = cur;
    prev = cur;
    if(args[1] == NULL || vars  == NULL)
    {
        return NULL;
    }
        while(cur != NULL)
        {
           if(ft_strncmp(cur->data,args[1], ft_strlen(args[1])) == 0)
           {
               prev->next = cur->next;
           }
           else
           {
               prev = cur;
           }
               cur = cur->next;
        }
        return list;
} 
t_vars  *remove_elemet(char *str, t_vars **vars)
{
    t_vars *cur = NULL;
    t_vars *prev = NULL;
    t_vars *list = NULL;
    
    cur = *vars;
    list = cur;
    prev = cur;
    if(str == NULL || vars  == NULL)
    {
        return NULL;
    }
        while(cur != NULL)
        {
           if(ft_strncmp(cur->data,str, ft_strlen(str)) == 0)
           {
               prev->next = cur->next;
           }
           else
           {
               prev = cur;
           }
               cur = cur->next;
        }
        return list;
} 


void ft_modify(char *str,char *str2, t_vars **declare)
{
    t_vars *cur = NULL;
    cur = *declare;
    char *tmp;
    while(cur != NULL)
    {
       if(ft_strncmp(cur->data,str, ft_strlen(str)) == 0)
       {
            tmp = cur->data;
            cur->data = ft_strjoin(ft_substr(cur->data, 0, ft_strlenCher(cur->data, '=') + 1), str2);
            free(tmp);
       }
    cur = cur->next;
    }
}