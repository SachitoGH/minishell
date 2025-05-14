# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssenas-y <ssenas-y@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 22:36:16 by ssenas-y          #+#    #+#              #
#    Updated: 2024/06/11 14:08:25 by ssenas-y         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

PARS        = main.c \
              parsing/parser.c \
              parsing/ft_strtok.c \
              parsing/ft_strtok_utils.c \
              parsing/utils.c \
              parsing/utils_2.c \
              parsing/utils_3.c \
              parsing/utils_4.c \
              parsing/parser_utils.c \
              parsing/check_env_var.c \
              parsing/check_env_var_utils.c

EXE         = exec/builtins.c \
              exec/exec.c \
              exec/heredoc.c \
              exec/signals.c \
              exec/utils.c

BIN         = builtins/echo.c \
              builtins/cd.c \
              builtins/export.c \
              builtins/unset.c \
              builtins/env.c \
              builtins/exit.c \
              builtins/pwd.c \
              builtins/utils.c
              
LIBFT       = ./libft/

NAMELFT     = ./libft/libft.a

OBJS        = $(PARS:.c=.o) $(EXE:.c=.o) $(BIN:.c=.o)

CC          = gcc

CFLAGS      = -Wall -Wextra #-Werror

INC         = -I./inc/

all:        $(OBJS) $(NAME)

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $(INC) $< -o $(<:.c=.o)
	@echo "Compiling OK!"

$(NAME): $(OBJS)
	@make -C ./libft
	@echo "Linking $^"
	@$(CC) $(CFLAGS) $(OBJS) $(NAMELFT) -lreadline -L/Users/$(USER)/homebrew/opt/readline/lib -I/Users/$(USER)/homebrew/opt/include/readline/ -ltermcap -o $@
	@echo "Executable created!"

clean:
	@echo "Cleaning objects..."
	@rm -f $(OBJS)
	@echo "Cleaned up!"

fclean: clean
	@make fclean -C ./libft
	@echo "Removing executable..."
	@rm -f $(NAME)
	@echo "Removed!"

re: fclean all

.PHONY: all clean fclean re
