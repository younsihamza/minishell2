# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 17:16:48 by ichouare          #+#    #+#              #
#    Updated: 2023/04/03 14:54:42 by hyounsi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

FLAG = -Wall -Wextra  -Werror 

HEADER = ./minishell.h

FLAGS = -I/Users/$(USER)/Desktop/homebrew/opt/readline/include

# FLAGD = -L/Users/$(USER)/homebrew/opt/readline/lib


SRCS =  main.c tree.c transform_cmd.c tools.c lexeer.c heredoc.c ft_strdup.c ft_split.c ft_putstr.c  execute.c create_list.c ft_unset.c  handle_signal.c\


OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS) 
	$(CC) $(FLAG)  $(FLAGS) $(FLAGD) $^ -o $@  -lreadline  -L/Users/$(USER)/Desktop/homebrew/opt/readline/lib
 
	
%.o : %.c  $(HEADER)
	$(CC) $(FLAG)   $(FLAGS) $(FLAGD) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all 