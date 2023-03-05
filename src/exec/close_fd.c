/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 06:52:38 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/05 16:05:24 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	close_fd(t_pipe *args, t_fd *fd_list)
{
	int	i;

	i = 0;
	while (i < args->argc - 1)
	{
		close(fd_list[i].fd[0]);
		close(fd_list[i].fd[1]);
		i++;
	}
}
