/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:05:38 by ichouare          #+#    #+#             */
/*   Updated: 2023/05/11 20:28:46 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>

int	g_s[2];
typedef struct lexer
{
	int	i;
	int	j;
	int	spaces;
}	t_lexer;

typedef struct vars
{
	char		*data;
	struct vars	*next;
}	t_vars;

typedef struct node
{
	char		*data;
	int			i;
	int			space;
	int			status;
	char		*type;
	struct node	*next;
}	t_node;

typedef struct tree_node
{
	t_node				*tokn;
	struct tree_node	*left;
	struct tree_node	*right;
}	t_tree;

typedef struct data{
	t_node		**op;
	char		***cmd;
	char		***deriction;
	char		***heredoc;
	int			*status;
	char		*pathhome;
}	t_data;

typedef struct help_var
{
	int		i;
	int		fd;
	int		fd1;
	int		fd2;
	char	*infile;
	char	*outfile;
	char	*outappend;
	char	*heredoc;
	int		id;
	int		lenpipe;
	int		pipeincrement;
	char	*path;
	char	**split_path;
	char	**envs;
	char	*tmp;
	char	*joincmd;
	int		**fds;
	char	**file;
	int		len;
	int		j;
	char	**splitvar;
	char	**command;
	char	**tmp2d;
	int		r;
	int		*file_descripter;
}t_help_var;

typedef struct declare
{
	char		*tmp;
	char		*std1;
	char		*std2;
	char		*content;
}	t_declare;
typedef struct env
{
	t_vars	*envv;
	t_vars	*declare;
}	t_env;

char	***checkherecode(char ***deriction, int len, int *status, t_vars *env);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
t_node	*ft_lstlast(t_node *lst);
void	add_back(t_node **lst, t_node *new);
t_node	*ft_lstnew(void *content, char *type, int space);
char	*ft_substr(char const *s, size_t start, size_t len);
int		ft_strncmp( const char *str1, const char *str2, size_t n);
t_tree	*bulid_tree(t_node *head, t_env *envir, char *pathHome);
int		ft_strchr(char *str, char a);
t_tree	*create_node_tree(t_node *tokn);
t_tree	*insert(t_tree *root, t_node *ptr);
int		len_list(t_node *head);
void	*ft_calloc(size_t nitems, size_t size);
int		check_error_parser(t_tree **q, int len);
t_node	*token(char *text);
char	**ft_join2d(char **env, char *var);
int		ft_strcmp(char *str1, char *str2);
int		ft_strlen2d(char **s1);
void	transform_cmd(t_node **rot, t_vars *env,
			t_vars **declare, char *pathhome);
int		ft_search(char *word, char to_find);
char	*get_env_arr(char *find, t_vars *env);
void	execute(t_data *var, t_vars *env, t_vars **declare);
void	ft_putstr(char *str, int fd);
void	add_envback(t_vars **lst, t_vars *new);
t_vars	*ft_lstlastenv(t_vars *lst);
t_vars	*ft_envnew(void *content);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
int		ft_strlencher(char *str, int a);
void	free2d(char **table);
void	handle_sigint(int sig);
void	ft_export(char **str, t_vars *env, t_vars **declare);
void	echo(char **cmd);
void	cd(char *p, t_data *d);
void	cmd_env(t_vars *env);
char	**ft_env(t_vars *vars);
char	*delimet(char *l);
void	ft_close(int **fd, int len);
t_vars	*ft_envnew(void *content);
t_vars	*ft_lstlastenv(t_vars *lst);
void	add_envback(t_vars **lst, t_vars *new);
t_vars	*get_env(char **env);
void	build_in_child(char **cmd, t_vars *env, t_vars **declare);
void	cmd1(char **cmd, t_vars *env, t_vars **declare);
void	find_file(t_help_var *v, char **deriction);
void	in_file(t_help_var *v, char **heredoctable);
void	ft_unset(char **args, t_vars *vars);
void	ft_unset_declare(char **args, t_vars **vars);
t_vars	*remove_elemet(char *str, t_vars **vars);
void	ft_modify(char *str, t_vars **declare);
void	ft_modify_env(char *str, t_vars *env);
int		out_file(t_help_var *v);
void	ft_tolower(char ***cmd);
void	cmd_help(t_help_var *v, t_node **rot);
void	convert_cmd(t_data *d, t_help_var *v, t_node **rot);
int		is_alpha(char *str);
void	add_id(t_node *head);
void	token_last(t_lexer *lex, char *text, t_node **head);
void	free_tree(t_tree *root);
void	makestack(t_tree *root, t_node **rot, int *i);
void	free_head(t_node *head);
t_tree	**make_queue(int len, t_tree *root);
void	token_sone(t_lexer *lex, char *text, t_node **list);
t_node	*simpletoken(char *text);
void	expand_one(char **data, char *tmp, t_vars *env);
t_node	*expand_two(char **data, t_node **str, t_vars *env);
void	join_data(char **data, char *tmp, char **tokn);
void	ft_inorder(t_node **rot, t_vars *env);
void	ft_func(t_tree *root, int len, t_env *envir, char *pathHome);
void	ft_expand(t_node *rot, t_vars *env);
void	ft_add_new(t_vars **declare, char *str, char *buffer1);
char	*ft_content(char *str);
void	free_head(t_node *head);
int		check_error(int i, char *text, t_node **head);
void	dups(char **deriction, char **heredoctable, int test);
void	help_me(t_help_var *v);
char	*herdoc_expand(char *data, t_vars *env);
char	*ft_itoa(int n);
#endif // !