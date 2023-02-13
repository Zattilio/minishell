/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:52:00 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/13 16:38:27 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	permission_denied(char **cmd)
{
	ft_putstr_fd("pipex: permission denied: ", 2);
	ft_putendl_fd(cmd[0], 2);
	free_tab (cmd);
	return (126);
}

int	command_not_found(char **path_tab, char **cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	free_tab(path_tab);
	free_tab(cmd);
	return (127);
}

int	error_ft_strjoin3(char **path_tab, char **cmd)
{
	ft_putstr_fd("pipex: error ft_strjoin3", 2);
	free_tab(path_tab);
	free_tab(cmd);
	return (7);
}
