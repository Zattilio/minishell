/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:07:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/28 20:08:24 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libft/src/libft.h"
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

# define _XOPEN_SOURCE 700
# define _GNU_SOURCE

# ifndef GLOBAL
int	g_return_value = 0;
# endif

/* command_line_interface */
void	print_minishell_title(void);

/* builtins */
void	cd(char *path);

#endif
