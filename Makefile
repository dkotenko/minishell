# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clala <clala@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 16:58:46 by clala             #+#    #+#              #
#    Updated: 2021/04/16 23:38:41 by clala            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ALL_C =	main.c \
		exec_bin.c \
		do_cd.c \
		environ.c \
		input.c \
		signals.c \
		handle_status_aux.c \
		environ_methods.c \
		init.c \
		path.c \
		cmd.c \
		do_cd_aux.c \
		do_cd_check_dir.c \
		do_builtins.c

SRCDIR = ./src
OBJDIR = ./objs
ALL_OBJ = $(ALL_C:%.c=%.o)
OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = minishell

INCLUDES_DIR = ./includes
ALL_INCLUDES = 	minishell.h \
				const.h 
INCLUDES =  $(addprefix $(INCLUDES_DIR)/, $(ALL_INCLUDES))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)
CC = gcc
FLAGS = -Wall -Wextra -Werror -g

all: lib $(OBJDIR) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -o $@ $(LIBFT)

$(LIBFT): lib

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@ -I./$(INCLUDES_DIR) -I./$(LIBFT_DIR)/includes 

$(OBJDIR):
	/bin/mkdir -p $(OBJDIR)

lib:
	@$(COMP_LIB)

clean:
	@/bin/rm -rf $(OBJDIR)
	@$(COMP_LIB) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@$(COMP_LIB) fclean

re: fclean all

debug:: FLAGS+=-g -fsanitize=address
debug:: re

.PHONY: lib clean fclean all re debug