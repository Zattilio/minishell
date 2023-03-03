/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 06:52:19 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/03 17:39:00 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/* int	ft_error(int n, t_node *root, int *pids, t_fd *fd_list)
{
	if ((n >= 4 || n == 0 || n == 1) && n != 7 && n != 10)
	{
		close_fd(root, fd_list);
		free(pids);
		free(fd_list);
	}
	if (n == 2)
		ft_putendl_fd("minishell: error calloc pids", 2);
	if (n == 3)
	{
		ft_putendl_fd("minishell: error calloc fd_list", 2);
		free(pids);
	}
	if (n == 4)
		ft_putendl_fd("minishell: error pipe", 2);
	if (n == 5)
		ft_putendl_fd("minishell: error fork", 2);
	if (n == 6)
		ft_putendl_fd("minishell: could not execve", 2);
	if (n == 7)
		ft_putendl_fd("minishell: '': Command not found", 2);
	exit(n);
}
 */
