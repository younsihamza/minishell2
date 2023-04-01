/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:14:03 by ichouare          #+#    #+#             */
/*   Updated: 2023/04/01 13:28:45 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


t_vars  *ft_unset(char **args, t_vars **vars)
{
    t_vars *cur = NULL;
    t_vars *prev = NULL;
    t_vars *list = NULL;
    int i = 0;
    cur = *vars;
    list = cur;
    prev = cur;
    if(args[1] == NULL || vars  == NULL)
    {
        return NULL;
    }
    i = 1;
    while(args[i])
    {
      while(cur != NULL)
        {
            if(ft_strlenCher(args[i], '=') != -1)
            {
                printf("unset: `%s': not a valid identifier\n", args[i]);
                break;
            }
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
        i++; 
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


void ft_modify(char *str, t_vars **declare)
{
    t_vars *cur = NULL;
    char *tmp = NULL;
    char *buffer1 = NULL;
    char *buffer2 = NULL;
    cur = *declare;
    if((ft_strlen(str) == 1 && str[0] == '=') || str[0] == '=')
    { 
        printf("bash: export: `%s': not a valid identifier\n", str);
        return;
    }
    if(ft_strlenCher(str,'=') != -1)
    {
        buffer1 = ft_substr(str, 0, ft_strlenCher(str, '=') + 1);
        buffer2 = ft_substr(str, ft_strlenCher(str, '=') + 1, ft_strlen(str));
        tmp = buffer2;
        buffer2 = ft_strjoin("\"", buffer2);
        free(tmp);
        tmp = buffer2;
        buffer2 = ft_strjoin(buffer2, "\"");
        free(tmp);
        tmp = buffer1;
        buffer1 = ft_strjoin(buffer1, buffer2);
        free(tmp);  
    }
    else
    {
        buffer1 = str;
    }

    int j = 0;
    while(cur != NULL)
    {
       if(ft_strncmp(cur->data,str, ft_strlen(ft_substr(cur->data, 0, ft_strlenCher(cur->data, '=')))) == 0)
       {
            j= 1;
            tmp = cur->data;
            if(ft_strlenCher(str, '=') == -1)
                return;
            cur->data = ft_strjoin(ft_substr(cur->data, 0, ft_strlenCher(cur->data, '=') + 1), buffer2);
            free(tmp);
            return ;
       }
    cur = cur->next;
    }
    if(j == 0)
       add_envback(declare, ft_envnew(buffer1)); 
}



void ft_modify_env(char *str, t_vars **env)
{
    char *buffer1; 
    char *buffer2;
    char *tmp;
    int j = 0;
    t_vars  *cur = NULL;
    cur = *env;
    if((ft_strlen(str) == 1 && str[0] == '=') || str[0] == '=')
        return ;
    buffer1 = ft_substr(str, 0, ft_strlenCher(str, '=') + 1);
    buffer2 = ft_substr(str, ft_strlenCher(str, '=') + 1, ft_strlen(str));
    while(cur != NULL)
    {
       if(ft_strncmp(cur->data,str, ft_strlen(ft_substr(cur->data, 0, ft_strlenCher(cur->data, '=')))) == 0)
       {
            j = 1;
            tmp = cur->data;
            if(ft_strlenCher(str, '=') == -1)
                return;
            cur->data = ft_strjoin(ft_substr(cur->data, 0, ft_strlenCher(cur->data, '=') + 1), buffer2);
            free(tmp);
            return ;
       } 
       cur = cur->next;
    }
    if(j == 0)
    {
        tmp = buffer1;
        buffer1 = ft_strjoin(buffer1, buffer2);
        add_envback(env, ft_envnew(buffer1)); 
    }

}