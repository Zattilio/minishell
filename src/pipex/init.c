/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 05:35:02 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/13 16:42:42 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	check_empty(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->argc)
	{
		if (ft_strncmp(args->argv[i], "", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_pipex(t_arg *args, int **pids, t_fd **fd_list)
{
	if (args->argc < 4 || check_empty(args))
		ft_error(7, args, NULL, NULL);
	*pids = ft_calloc(args->argc - 3, sizeof(**pids));
	if (*pids == NULL)
		ft_error(2, args, NULL, NULL);
	*fd_list = ft_calloc(args->argc - 4, sizeof(**fd_list));
	if (*fd_list == NULL)
		ft_error(3, args, *pids, *fd_list);
}

void	init_pipes(t_arg *args, int *pids, t_fd *fd_list)
{
	int	i;

	i = 0;
	while (i < args->argc - 4)
	{
		if (pipe((fd_list[i]).fd) == -1)
			ft_error(4, args, pids, fd_list);
		i++;
	}
}

void	init_fork(t_arg *args, int *pids, t_fd *fd_list)
{
	int	i;

	i = 0;
	if (check_heredoc(args))
		i = 1;
	while (i < args->argc - 3 && is_parent_process(pids, i))
	{
		pids[i] = fork();
		if (pids[i] < 0)
			ft_error(5, args, pids, fd_list);
		i++;
	}
}

t_arg	*init_arg(int *argc, char **argv[], char **env[])
{
	t_arg	*args;

	args = malloc(sizeof(*args));
	if (args == NULL)
		exit(10);
	args->argc = *argc;
	args->argv = *argv;
	args->env = *env;
	return (args);
}
