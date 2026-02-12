# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wedu <wedu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 15:30:00 by wedu              #+#    #+#              #
#    Updated: 2026/02/12 17:49:51 by wedu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -lreadline

SRCDIR		= src
OBJDIR		= obj

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= $(SRCDIR)/main.c \
			  $(SRCDIR)/parser.c \
			  $(SRCDIR)/lexer.c \
			  $(SRCDIR)/built_ins.c \
			  $(SRCDIR)/built_ins2.c \
			  $(SRCDIR)/executor.c \
			  $(SRCDIR)/signals.c \
			  $(SRCDIR)/utils.c \
			  $(SRCDIR)/env_utils.c \
			  $(SRCDIR)/redirections.c \
			  $(SRCDIR)/pipes.c

OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

HEADERS		= $(SRCDIR)/minishell.h

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(SRCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
