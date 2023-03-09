/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:52:58 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/09 14:04:20 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	valid_n(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != '-')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	exec_echo(char **cmd)
{
	t_bool	print_nl;
	int		i;

	print_nl = TRUE;
	i = 1;
	if (cmd == NULL || cmd[0] == NULL || ft_strlen(cmd[0]) != 4
		|| ft_strncmp(cmd[0], "echo", 4) != 0)
		return (1);
	while (cmd[i] && valid_n(cmd[i]))
	{
		print_nl = FALSE;
		i++;
	}
	while (i < get_nb_str(cmd))
	{
		ft_printf("%s", cmd[i]);
		if (i != get_nb_str(cmd) - 1)
			ft_printf(" ");
		i++;
	}
	if (print_nl == TRUE)
		ft_printf("\n");
	return (0);
}
