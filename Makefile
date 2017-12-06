# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppatel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/22 11:56:58 by ppatel            #+#    #+#              #
#    Updated: 2017/08/22 11:57:06 by ppatel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall \
		-Wextra \
		-Werror \

NAME = lem-in

SDIR = srcs

ODIR = objects

SRCS = $(SDIR)/main.c \
	   $(SDIR)/parse1.c \
	   $(SDIR)/parse2.c \
	   $(SDIR)/findpath.c \
	   $(SDIR)/find_shortest.c \
	   $(SDIR)/options.c \
	   $(SDIR)/parseroom.c \
	   $(SDIR)/move_print.c \
	   $(SDIR)/print.c \
	   $(SDIR)/check_clear.c \
	   $(SDIR)/tools1.c \
	   $(SDIR)/tools2.c \
	   $(SDIR)/free_all.c \

OBJ = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)

HDRS = -I./includes \
	   -I./libft/includes

LIBFT = ./libft/libft.a

LIBS = -L./libft/ -lft

all : $(NAME)

$(NAME): $(ODIR) $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(LIBS) $(OBJ) -o $@
	@echo "lem-in created."

$(ODIR):
	@mkdir objects

$(ODIR)/%.o: $(SDIR)/%.c
	@$(CC) $(FLAGS) -c $< $(HDRS) -o $@
	@echo "Object created."

$(LIBFT):
	@make -C libft/

clean:
	@rm -rf $(ODIR)
	@make clean -C libft
	@echo "Objects deleted."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "Executable deleted."

re: fclean all

.PHONY: all clean fclean re
