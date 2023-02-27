/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commain.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:06:13 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/27 18:29 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_return_value = 0;
u

int	main(int argc, char *argv[], char *env[])
{
	char	do_;
	char	*command_buf;

	do_ = 1;
	print_minishell_title();
	while (do_)
	{
		if (g_return_value == 0)
			command_buf = readline("\033[0;32m➜ \033[0;36mminishell$ \033[0m");
		else
			command_buf = readline("\033[0;31m➜ \033[0;36mminishell$ \033[0m");
		if (ft_strlen(command_buf) > 0)
			add_history(command_buf);
		if (!ft_strcmp(command_buf, "exit"))
			do_ = 0;
		g_return_value = 1;
	}
	rl_clear_history();
	(void)argc;
	(void)argv;
	(void)env;
	return (g_return_value);
}
