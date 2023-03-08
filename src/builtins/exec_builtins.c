/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:43:07 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 13:53:11 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exec_builtins(char *arg[], char *env[])
{
/* 	if (!ft_strcmp(arg[0], "cd"))
		cd(arg, env);
	if (!ft_strcmp(arg[0], "exit"))
		ft_exit(arg, env);
	if (!ft_strcmp(arg[0], "pwd"))
		pwd(arg, env);
	if (!ft_strcmp(arg[0], "echo"))

	if (!ft_strcmp(arg[0], "export"))

	if (!ft_strcmp(arg[0], "unset"))

	if (!ft_strcmp(arg[0], "env"))

	return (-1); */
	(void)arg;
	(void)env;
	return (0);
}

static int	check_builtins(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

int	exec_cmd(t_pipe *pipe, char *path, char *arg[])
{
	if (check_builtins(arg[0]))
		return (exec_builtins(arg, pipe->prm->env));
	else
		return (execve(path, arg, pipe->prm->env));
}
