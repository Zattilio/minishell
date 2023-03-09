/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:52:00 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/09 10:55:16 by mbocquel         ###   ########.fr       */
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
	(void)path_tab;
	ft_put3str_fd("minishell: ", cmd[0], ": Command not found\n", 2);
	return (127);
}

int	path_not_found(char **path_tab, char **cmd)
{
	(void)path_tab;
	return (127);
	(void)cmd;
}

int	error_ft_strjoin3(char **path_tab, char **cmd)
{
	ft_putstr_fd("minishell: error ft_strjoin3\n", 2);
	return (7);
	(void)path_tab;
	(void)cmd;
}
