/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 05:35:02 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/05 16:03:31 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	init_pipex(t_pipe *args, int **pids, t_fd **fd_list)
{
	*pids = ft_calloc(args->argc + 1, sizeof(**pids));
	if (*pids == NULL)
		ft_error(2, args, NULL, NULL);
	*fd_list = ft_calloc(args->argc, sizeof(**fd_list));
	if (*fd_list == NULL)
		ft_error(3, args, *pids, *fd_list);
}


void	init_pipes(t_pipe *args, int *pids, t_fd *fd_list)
{
	int	i;

	i = 0;
	while (i < args->argc - 1)
	{
		if (pipe((fd_list[i]).fd) == -1)
			ft_error(4, args, pids, fd_list);
		i++;
	}
}

void	init_fork(t_pipe *args, int *pids, t_fd *fd_list)
{
	int	i;

	i = 0;
	//if (check_heredoc(args))
	//	i = 1;
	while (i < args->argc && is_parent_process(pids, i))
	{
		pids[i] = fork();
		if (pids[i] < 0)
			ft_error(5, args, pids, fd_list);
		i++;
	}
}

