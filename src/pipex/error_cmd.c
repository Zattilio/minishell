/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:52:00 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/03 15:20:31 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_put2str_fd(char *s1, char *s2, int fd)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}

void	ft_put3str_fd(char *s1, char *s2, char *s3, int fd)
{
	char	*tmp;

	tmp = ft_strjoin3(s1, s2, s3);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}

int	permission_denied(char **cmd)
{
	ft_put3str_fd("minishell: ", cmd[0], ": Permission denied\n", 2);
	free_tab (cmd);
	return (126);
}

int	command_not_found(char **path_tab, char **cmd)
{
	ft_put3str_fd("minishell: ", cmd[0], ": Command not found\n", 2);
	free_tab(path_tab);
	free_tab(cmd);
	return (127);
}

int	path_not_found(char **path_tab, char **cmd)
{
	free_tab(path_tab);
	free_tab(cmd);
	return (127);
}

int	error_ft_strjoin3(char **path_tab, char **cmd)
{
	ft_putstr_fd("minishell: error ft_strjoin3\n", 2);
	free_tab(path_tab);
	free_tab(cmd);
	return (7);
}
