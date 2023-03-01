/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:32:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/01 04:01:05 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

unsigned char	g_return_value = 0;



int	main(int argc, char *argv[], char *env[])
{
	char	do_;
	char	*cmd_buf;
	char	*cmd;

	init_signal();
	print_minishell_title();
	do_ = 1;
	while (do_)
	{
		print_new_prompt(&cmd_buf);
		if (cmd_buf == NULL)
			return (0);
		cmd = ft_strtrim(cmd_buf, " ");
		if (ft_strlen(cmd) > 0 && cmd_buf[0] != ' ')
			add_history(cmd);
		free(cmd_buf);
		if (!ft_strncmp(cmd, "exit ", 5) || !ft_strcmp(cmd, "exit"))
			ft_exit(cmd, &do_);
		if (!ft_strncmp(cmd, "pwd ", 4) || !ft_strcmp(cmd, "pwd"))
			pwd();
		if (!ft_strncmp(cmd, "cd ", 3) || !ft_strcmp(cmd, "cd"))
			cd(&cmd[2]);
	}
	rl_clear_history();
	(void)argc;
	(void)argv;
	(void)env;
	return (g_return_value);
}
