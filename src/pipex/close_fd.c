/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 06:52:38 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/13 16:38:24 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_fd(t_arg *args, t_fd *fd_list)
{
	int	i;

	i = 0;
	while (i < args->argc - 4)
	{
		close(fd_list[i].fd[0]);
		close(fd_list[i].fd[1]);
		i++;
	}
}
