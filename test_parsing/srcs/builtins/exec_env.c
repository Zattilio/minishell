/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:20:38 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/07 18:29:35 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	exec_env(t_param *prm, char **cmd)
{
	if (cmd == NULL || cmd[0] == NULL || ft_strlen(cmd[0]) != 3
		|| ft_strncmp(cmd[0], "env", 3) != 0)
		return ;
	print_env(prm);
}

void	exec_export(t_param *prm, char **cmd)
{
	int	i;

	i = 1;
	if (cmd == NULL || cmd[0] == NULL || ft_strlen(cmd[0]) != 6
		|| ft_strncmp(cmd[0], "export", 6) != 0)
		return ;
	while (i < get_nb_str(cmd))
	{
		export_env(prm, cmd[i]);
		i++;
	}
}

void	exec_unset(t_param *prm, char **cmd)
{
	int	i;

	i = 1;
	if (cmd == NULL || cmd[0] == NULL || ft_strlen(cmd[0]) != 5
		|| ft_strncmp(cmd[0], "unset", 5) != 0)
		return ;
	while (i < get_nb_str(cmd))
	{
		unset_env(prm, cmd[i]);
		i++;
	}
}
