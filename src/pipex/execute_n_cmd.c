/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_n_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:15:18 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/13 16:38:27 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	execute_first_cmd(t_arg *args, t_fd *fd_list)
{
	int		fd_input;

	if (!check_heredoc(args))
	{
		dup2(fd_list[0].fd[1], STDOUT_FILENO);
		close_fd(args, fd_list);
		fd_input = open(args->argv[1], O_RDONLY, 00600);
		if (fd_input == -1)
		{
			if (!access(args->argv[1], F_OK))
				ft_putstr_fd("pipex: permission denied: ", 2);
			else
				ft_putstr_fd("pipex: no such file or directory: ", 2);
			ft_putendl_fd(args->argv[1], 2);
			return (1);
		}
		dup2(fd_input, 0);
		close(fd_input);
		return (execute_cmd(args, 2));
	}
	return (0);
}

void	execute_middle_cmd(t_arg *args, int *pids, t_fd *fd_list)
{
	int	i;

	i = 1;
	while (i < args->argc - 4)
	{
		if (pids[i] == 0)
		{
			dup2(fd_list[i].fd[1], 1);
			dup2(fd_list[i - 1].fd[0], 0);
			close_fd(args, fd_list);
			ft_error(execute_cmd(args, i + 2), args, pids, fd_list);
		}
		i++;
	}
}

int	execute_last_cmd(t_arg *args, t_fd *fd_list)
{
	int	fd_output;

	dup2(fd_list[args->argc - 5].fd[0], STDIN_FILENO);
	close_fd(args, fd_list);
	if (!check_heredoc(args))
		fd_output = open(args->argv[args->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 00644);
	else
		fd_output = open(args->argv[args->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 00644);
	if (fd_output == -1)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(args->argv[args->argc - 1], 2);
		return (1);
	}
	dup2(fd_output, 1);
	close(fd_output);
	return (execute_cmd(args, args->argc - 1 - 1));
}
