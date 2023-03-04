/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 05:34:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/04 14:15:54 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	ft_wait(t_pipe *args, int *pids)
{
	int	i;

	i = 0;
	while (i < args->argc)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}
