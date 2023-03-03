# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 10:48:53 by mbocquel          #+#    #+#              #
#    Updated: 2023/03/03 17:37:51 by jlanza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SOURCES_DIR = ./src/

BUILD_DIR = ./build/

SOURCES =	exec/exec_pipe.c \
			exec/exec_root.c \
			exec/get_path_name.c \
			exec/execute_cmd.c \
			exec/execute_n_cmd.c \
			exec/is_parent_process.c \
			exec/ft_error.c \
			exec/ft_putnstr_fd.c \
			exec/close_fd.c \
			exec/error_cmd.c \
			exec/ft_wait.c \
			exec/init.c \
			exec/here_doc.c \
			command_line_interface/command_line_interface.c \
			command_line_interface/signal.c \
			builtins/ft_cd.c \
			builtins/ft_pwd.c \
			builtins/ft_exit.c \
			maxence/garbage_2.c \
			maxence/garbage.c \
			maxence/get_env.c \
			maxence/lexeur.c \
			maxence/lexeur_utils.c \
			maxence/parseur.c \
			maxence/print_ast.c \
			maxence/test_parsing.c \
			maxence/utils.c \
			main.c

OBJECTS		= $(addprefix ${BUILD_DIR}, ${SOURCES:.c=.o})

DEPS := $(OBJECTS:.o=.d)

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP

RM = rm -rf

LIBFT_DIR = libft/

CLIB = -Llibft -lft -lreadline

all: $(NAME)

$(BUILD_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
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
