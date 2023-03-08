/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:52:58 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 12:56:38 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_echo(char **cmd)
{
	t_bool	print_nl;
	int		i;

	print_nl = TRUE;
	i = 0;
	if (cmd == NULL || cmd[0] == NULL || ft_strlen(cmd[0]) != 4
		|| ft_strncmp(cmd[0], "echo", 4) != 0)
		return ;
	if (cmd[1] && ft_strlen(cmd[1]) == 2 && ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		print_nl = FALSE;
		i++;
	}
	while (++i < get_nb_str(cmd))
	{
		ft_printf("%s", cmd[i]);
		if (i != get_nb_str(cmd) - 1)
			ft_printf(" ");
	}
	if (print_nl == TRUE)
		ft_printf("\n");
}
