/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:52:00 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 19:19:40 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	permission_denied(char **cmd)
{
	ft_put3str_fd("minishell: ", cmd[0], ": Permission denied\n", 2);
	return (126);
}

int	command_not_found(char **path_tab, char **cmd)
{
	ft_put3str_fd("minishell: ", cmd[0], ": Command not found\n", 2);
	free_tab(path_tab);
	return (127);
}

int	path_not_found(char **path_tab, char **cmd)
{
	free_tab(path_tab);
	return (127);
	(void)cmd;
}

int	error_ft_strjoin3(char **path_tab, char **cmd)
{
	ft_putstr_fd("minishell: error ft_strjoin3\n", 2);
	free_tab(path_tab);
	return (7);
	(void)cmd;
}
