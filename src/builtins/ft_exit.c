/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 04:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/01 04:08:04 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(char *cmd, char *do_)
{
	int	i;

	*do_ = 0;
	cmd += 4;
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	if (!ft_isint(cmd))
	{
		cmd[i] = '\0';
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n", cmd);
		g_return_value = 2;
	}
	else if (cmd[i] == ' ')
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		g_return_value = 1;
	}
	else
		g_return_value = ft_atoi(cmd);
}
