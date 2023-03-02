/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:07:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/02 19:49:49 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/src/libft.h"
# include "./pipex.h"
# include "../maxence/parsing.h"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define VERT "\033[0;32m"
# define ROUGE "\033[0;31m"
# define CYAN "\033[0;36m"
# define GRAS_START "\e[1m"
# define GRAS_END "\e[0m"
# define RESET_COLOR "\033[0m"

extern unsigned char	g_return_value;

/* command_line_interface */
void	print_minishell_title(void);
void	readline_new_prompt(char **cmd_buf);
void	printf_new_prompt(void);
void	init_signal(void);

/* builtins */
void	ft_cd(char *arg[], char *env[]);
void	ft_pwd(char *arg[], char *env[]);
void	ft_exit(char *arg[], char *env[], char *do_);

#endif
