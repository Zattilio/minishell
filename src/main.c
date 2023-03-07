/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:32:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/07 18:56:57 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

unsigned char	g_return_value = 0;

int	main(int argc, char *argv[], char *env[])
{
	char	do_;
	char	*cmd_buf;
	char	*cmd;
	t_param	prm;
	t_node	*root;

	cmd = NULL;
	if (argc != 1)
		return (ft_printf_fd(2, "minishell: too many arguments"), 1);
	ft_memset(&prm, 0, sizeof(t_param));
	print_minishell_title();
	do_ = 1;
	while (do_)
	{
		init_signal();
		prm.source.cur = 0;
		readline_new_prompt(&cmd_buf);
		if (cmd_buf == NULL)
			return (ft_printf("exit\n"), 0);
		cmd = ft_strtrim(cmd_buf, " ");
		if (ft_strlen(cmd) > 0 && cmd_buf[0] != ' ')
			add_history(cmd);
		free(cmd_buf);

		prm.source.line = cmd;
		prm.source.line_size = ft_strlen(cmd);
		garbage_col(&prm, prm.source.id, cmd);

		root = parsing(&prm);
		exec_root(&prm, root, env);

		empty_garbage(&prm, prm.source.id);
		(prm.source.id)++;
	}
	empty_garbage(&prm, -1);
	rl_clear_history();
	return (g_return_value);
	(void)argc;
	(void)argv;
	(void)env;
}
