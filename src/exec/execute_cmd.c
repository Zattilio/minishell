/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 06:52:28 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/07 03:47:23 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"


int	execute_cmd(t_pipe *args, int n_cmd)
{
	char	**cmd;
	char	*path_cmd;
	int		return_value;

	cmd = args->argv[n_cmd]->cmd;
	if (cmd == NULL)
		return (1);
	return_value = get_path_name(args, &path_cmd, cmd);
	if (return_value != 0)
		return (return_value);
	if (execve(path_cmd, cmd, args->env) == -1)
	{
		free(path_cmd);
		return (command_not_found(cmd, cmd));
	}
	return (6);
}
