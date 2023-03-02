/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:32:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/01 19:07:53 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

unsigned char	g_return_value = 0;
/*
int	main(int argc, char *argv[], char *env[])
{
	char	do_;
	char	*cmd_buf;
	char	*cmd;
	t_param prm;

	init_signal();
	ft_memset(&prm, 0, sizeof(t_param));
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
		prm.source.line = cmd;
		prm.source.line_size = ft_strlen(cmd);
		(prm.source.id)++;
		garbage_col(&prm, cmd);
		//ok pour envoie vers parsing puis exec.
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
}*/

int	main(int argc, char *argv[], char *env[])
{
	char	do_;
	char	*cmd_buf;
	char	*cmd;

	if (argc != 1)
		return (ft_printf_fd(2, "minishell: too many arguments"), 1);
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

		simple_parseur(cmd, &env);
	}
	rl_clear_history();
	return (g_return_value);
}
