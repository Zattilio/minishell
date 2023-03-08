/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 04:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 18:17:40 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_exit(t_param *prm, char *arg[])
{
	int	i;

	prm->do_ = 0;
	i = 0;
	if (!ft_isint(arg[1]))
	{
		arg[1][i] = '\0';
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n", arg[1]);
		g_return_value = 2;
	}
	else if (arg[1][i] == ' ')
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		g_return_value = 1;
	}
	else
		g_return_value = ft_atoi(arg[1]);
	return (0);
}
