/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:40:40 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/02 16:51:12 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_nb_arguments_cd(char *arg[])
{
	int	i;

	i = 1;
	while (arg[i])
	{
		i++;
	}
	if (i > 1)
		return (1);
	return (0);
}

void	ft_cd(char *arg[], char *env[])
{
	int		i;
	char	*new_path;

	i = 0;
	if (arg[0] == NULL)
		g_return_value = 0;
	else if (check_nb_arguments_cd(arg))
	{
		ft_printf("minishell: cd: too many arguments\n");
		g_return_value = 1;
	}
	else if (chdir(arg[1]) == -1)
	{
		new_path = ft_strjoin("./", arg[1]);
		if (chdir(new_path) == -1)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", arg[1]);
			g_return_value = 1;
		}
		else
			g_return_value = 0;
		free(new_path);
		(void)env;
	}
}
