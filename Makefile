# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 17:16:48 by ichouare          #+#    #+#              #
#    Updated: 2023/03/29 17:42:59 by ichouare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

FLAG = -Wall -Wextra  -Werror 

HEADER = ./minishell.h

FLAGS = -I/$(USER)/ichouare/homebrew/opt/readline/include

FLAGD = -L/Users/$(USER)/homebrew/opt/readline/lib


SRCS =  main.c tree.c transform_cmd.c tools.c lexeer.c heredoc.c ft_strdup.c ft_split.c ft_putstr.c  execute.c create_list.c \


OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS) 
	$(CC) $(FLAG) -lreadline $(FLAGS) $(FLAGD) $^ -o $@
 
	
%.o : %.c  $(HEADER)
	$(CC) $(FLAG)  $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all 