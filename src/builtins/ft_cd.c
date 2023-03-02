/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:40:40 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/01 19:21:09 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_cd_arguments(char *path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] != ' ')
		i++;
	if (path[i] == '\0')
		return (0);
	while (path[i] == ' ')
		i++;
	if (path[i] == '\0')
		return (0);
	return (1);
}

void	ft_cd(char *arg[], char *env[])
{
	int		i;
	char	*new_path;

	i = 0;
	while (path[i] == ' ')
		i++;
	if (path[0] == '\0')
		g_return_value = 0;
	else if (check_cd_arguments(&path[i]))
	{
		ft_printf("minishell: cd: too many arguments\n");
		g_return_value = 1;
	}
	else if (chdir(path) == -1)
	{
		new_path = ft_strjoin("./", &path[i]);
		if (chdir(new_path) == -1)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n", path);
			g_return_value = 1;
		}
		else
			g_return_value = 0;
		free(new_path);
	}
}
