
NAME = minishell

CC = cc 

FLAG = -Wall -Wextra  -Werror 

HEADER = ./minishell.h

FLAGS = -I/Users/$(USER)/homebrew/opt/readline/include

# FLAGD = -L/Users/$(USER)/homebrew/opt/readline/lib


SRCS =  main.c tree.c transform_cmd.c tools.c lexeer.c transforn_help.c heredoc.c ft_strdup.c ft_split.c ft_putstr.c  execute.c create_list.c ft_unset.c \
  		handle_signal.c buildin.c execute_1.c execute_2.c utils_1.c utils_2.c tools_1.c tools_2.c 


OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS) 
	$(CC) $(FLAG)  $(FLAGS) $(FLAGD) $^ -o $@  -lreadline  -L/Users/$(USER)/homebrew/opt/readline/lib
 
	
%.o : %.c  $(HEADER)
	$(CC) $(FLAG)   $(FLAGS) $(FLAGD) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all 