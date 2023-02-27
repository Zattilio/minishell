# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 10:48:53 by mbocquel          #+#    #+#              #
#    Updated: 2023/02/27 17:43:04 by jlanza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES_DIR = ./src/

BUILD_DIR = ./build/

SOURCES =	pipex/main_pipex.c \
			pipex/get_path_name.c \
			pipex/execute_cmd.c \
			pipex/execute_n_cmd.c \
			pipex/is_parent_process.c \
			pipex/ft_error.c \
			pipex/close_fd.c \
			pipex/error_cmd.c \
			pipex/ft_wait.c \
			pipex/init.c \
			pipex/here_doc.c \
			command_line_interface/command_line_interface.c

OBJECTS		= $(addprefix ${BUILD_DIR}, ${SOURCES:.c=.o})

DEPS := $(OBJECTS:.o=.d)

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3

RM = rm -rf

LIBFT_DIR = libft/

CLIB = -Llibft -lft -lreadline

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
