/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 04:01:22 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/02 16:58:31 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(char *arg[], char *env[], char *do_)
{
	int	i;

	*do_ = 0;
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
	(void)env;
}
