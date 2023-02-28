/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:32:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/28 19:03:57 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_return_value = 0;

void	handle_sigint(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	handle_sigquit(int sig)
{
	ft_printf("\33[2K\r");
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	pwd(void)
{
	char	*working_directory;

	working_directory = getcwd(NULL, 0);
	ft_printf("%s\n", working_directory);
	free(working_directory);
}

void	cd(char *path)
{
	int		i;
	char	*new_path;

	i = 0;
	if (path[0] != '\0')
	{
		while (path[i] == ' ')
			i++;
		if (chdir(path) == -1)
		{
			new_path = ft_strjoin("./", &path[i]);
			chdir(new_path);
			free(new_path);
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char				do_;
	char				*cmd_buf;

	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
	print_minishell_title();
	do_ = 1;
	while (do_)
	{
		if (g_return_value == 0)
			cmd_buf = readline("\033[1;32m➜  \033[0;36m\e[1mminishell$\e[0m \033[0m");
		else
			cmd_buf = readline("\033[1;31m➜  \033[0;36m\e[1mminishell$\e[0m \033[0m");
		if (cmd_buf == NULL)
			return (0);
		if (!ft_strcmp(cmd_buf, "exit"))
			do_ = 0;
		if (ft_strlen(cmd_buf) > 0)
			add_history(cmd_buf);
		if (!ft_strncmp(cmd_buf, "pwd ", 4) || !ft_strcmp(cmd_buf, "pwd"))
			pwd();
		if (!ft_strncmp(cmd_buf, "cd ", 3))
			cd(&cmd_buf[3]);
	}
	rl_clear_history();
	(void)argc;
	(void)argv;
	(void)env;
	return (g_return_value);
}
