# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clala <clala@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 16:58:46 by clala             #+#    #+#              #
#    Updated: 2021/01/28 19:51:45 by clala            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ALL_C =	main.c \
		exec_bin.c \
		do_cd.c \
		environ.c \
		quotation.c \
		input.c \
		signals.c \

SRCDIR = ./src
OBJDIR = ./objs
ALL_OBJ = $(ALL_C:%.c=%.o)
OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = minishell

INCLUDES_DIR = ./includes
INCLUDES = $(INCLUDES_DIR)/minishell.h


LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)
CC = gcc
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

all: $(LIBFT) $(OBJDIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(OBJDIR)
	$(CC) $(FLAGS) -I./$(INCLUDES_DIR) -I./$(LIBFT_DIR)/includes -c $< -o $@ 

$(OBJDIR):
	/bin/mkdir -p $(OBJDIR)

$(LIBFT): lib

lib:
	@$(COMP_LIB)

clean:
	@/bin/rm -rf $(OBJDIR)
	@$(COMP_LIB) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@$(COMP_LIB) fclean

re: fclean all

.PHONY: lib clean fclean all re