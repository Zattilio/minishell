# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 15:24:20 by jlanza            #+#    #+#              #
#    Updated: 2023/02/13 16:39:23 by jlanza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	src/pipex/main.c \
		src/pipex/get_path_name.c \
		src/pipex/execute_cmd.c \
		src/pipex/execute_n_cmd.c \
		src/pipex/is_parent_process.c \
		src/pipex/ft_error.c \
		src/pipex/close_fd.c \
		src/pipex/error_cmd.c \
		src/pipex/ft_wait.c \
		src/pipex/init.c \
		src/pipex/here_doc.c

BONUS_SRC =

LIBFT = ./libft/libft.a
OBJ = ${SRC:.c=.o}

NAME = pipex
NAME_BONUS = pipex
CFLAGS = -Wall -Wextra -Werror -g3
CC = cc
RM = rm -f
HEADER = src/include/pipex.h
HEADER_BONUS =

BONUS=no

ifneq ($(BONUS),no)
OBJ = ${BONUS_SRC:.c=.o}
SRC = $(BONUS_SRC)
HEADER = $(HEADER_BONUS)
endif

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ) $(HEADER)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

all: $(NAME)

bonus: $(HEADER_BONUS)
	@$(MAKE) BONUS=yes

clean:
	$(RM) *.o */*.o
	$(MAKE) fclean -C ./libft

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
