# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 10:48:53 by mbocquel          #+#    #+#              #
#    Updated: 2023/02/27 17:33:23 by mbocquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_parsing

SOURCES_DIR = ./srcs/

BUILD_DIR = ./build/

SOURCES = 	print_ast.c \
			lexeur.c \
			garbage.c \
			utils.c \
			test_parsing.c \
			parseur.c \
			
OBJECTS		= $(addprefix ${BUILD_DIR}, ${SOURCES:.c=.o})

DEPS := $(OBJECTS:.o=.d)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3

RM = rm -rf

LIBFT_DIR = libft/

CLIB = -Llibft -lft

all: $(NAME)

$(BUILD_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -O3 -c $< -o $@
	@echo "Compiling " $<

$(NAME):	$(OBJECTS)
			@echo
			@make -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(OBJECTS) $(CLIB) -o $(NAME)
			@echo "\nCreating ./"$(NAME)
			@echo "\n----- ALL DONE THANKS! -----\n"

clean:
	$(RM) $(BUILD_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM)  $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
