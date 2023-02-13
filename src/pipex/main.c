/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:00:06 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/13 16:38:27 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_arg	*args;
	t_fd	*fd_list;
	int		*pids;
	int		status;

	args = init_arg(&argc, &argv, &env);
	init_pipex(args, &pids, &fd_list);
	init_pipes(args, pids, fd_list);
	fork_heredoc(args, pids, fd_list);
	init_fork(args, pids, fd_list);
	if (pids[0] == 0)
		ft_error(execute_first_cmd(args, fd_list), args, pids, fd_list);
	execute_middle_cmd(args, pids, fd_list);
	if (pids[args->argc - 4] == 0)
		ft_error(execute_last_cmd(args, fd_list), args, pids, fd_list);
	close_fd(args, fd_list);
	ft_wait(args, pids);
	waitpid(pids[args->argc - 4], &status, 0);
	free(pids);
	free(fd_list);
	free(args);
	return (WEXITSTATUS(status));
}
