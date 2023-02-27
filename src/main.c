/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:32:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/27 19:01:12 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_return_value = 0;

int	main(int argc, char *argv[], char *env[])
{
	char	do_;
	char	*cmd_buf;

	do_ = 1;
	print_minishell_title();
	while (do_)
	{
		if (g_return_value == 0)
			cmd_buf = readline("\033[1;32m➜ \033[0;36m\e[1mminishell$\e[0m \033[0m");
		else
			cmd_buf = readline("\033[1;31m➜ \033[0;36m\e[1mminishell$\e[0m \033[0m");
		if (ft_strlen(cmd_buf) > 0)
			add_history(cmd_buf);
		if (!ft_strcmp(cmd_buf, "exit"))
			do_ = 0;
	}
	rl_clear_history();
	(void)argc;
	(void)argv;
	(void)env;
	return (g_return_value);
}
