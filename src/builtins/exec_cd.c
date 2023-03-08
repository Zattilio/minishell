/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:40:40 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 17:43:59 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_cd(t_param *prm, char *arg[])
{
	char	*new_path;
	
	if (get_nb_str(arg) != 2)
	{
		ft_printf("minishell: cd: wrong number of arguments\n");
		g_return_value = 1;
	}
	else if (chdir(arg[1]) == -1)
	{
		new_path = ft_strjoin("./", arg[1]);
		garbage_col(prm, prm->source.id, new_path);
		if (chdir(new_path) == -1)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", arg[1]);
			g_return_value = 1;
			return (1);
		}
		g_return_value = 0;
	}
	return (0);
}
