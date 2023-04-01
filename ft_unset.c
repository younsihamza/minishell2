#include "minishell.h"

int is_alpha(char *str)
{
    int i = 0;
    while (str[i])
    {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            i++;
        else 
            return (-1);
    }
    return (i);
}

void ft_unset(char **args, t_vars *vars)
{
    t_vars *cur ;
    t_vars *prev ;
    t_vars *list ;
    int i = 0;
    if(args[1] == NULL || vars  == NULL)
    {
        return ;
    }
    i = 1;
    while(args[i])
    {
        cur = vars;
        list = cur;
        prev = cur;
      while(cur != NULL)
        {
            if(is_alpha(args[i]) == -1)
            {
                printf("unset: `%s': not a valid identifier\n", args[i]);
                break;
            }
           if(ft_strncmp(cur->data,args[1], ft_strlen(args[1])) == 0)
           {
                list = cur;
                prev->next = cur->next;
                free(list);
           }
           else
               prev = cur;
            cur = cur->next;
        } 
        i++; 
    }
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
    if(ft_strchr(str,'=') != 0)
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
        free(buffer2);
        free(tmp);  
    }
    else
    {
        buffer1 = ft_strdup(str);
    }

    while(cur != NULL)
    {
       if(ft_strncmp(cur->data,str, ft_strlenCher(cur->data, '=')) == 0)
       {
            if(ft_strchr(str, '=') == 0)
            {
                free(buffer1);
                return;
            }
            free(cur->data);
            cur->data = buffer1;
            return;
       }
    cur = cur->next;
    }
       add_envback(declare, ft_envnew(buffer1));
}

void ft_modify_env(char *str, t_vars *env)
{
    t_vars  *cur = NULL;
    cur = env;
    if((ft_strlen(str) == 1 && str[0] == '=') || str[0] == '=')
        return ;
    while(cur != NULL)
    {
       if(ft_strncmp(cur->data,str, ft_strlenCher(str,'=')) == 0)
       {
            
            free(cur->data);
            cur->data = ft_strdup(str);
            return ;
       }
       cur = cur->next;
    }
        add_envback(&env, ft_envnew(strdup(str))); 

}