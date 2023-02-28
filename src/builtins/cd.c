/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:40:40 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/28 20:04:32 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_cd_arguments(char *path)
{
	int	i;

	// if (path[0] == '"')
	// 	check_cd_arguments_double_quote(path[1]);
	// if (path[0] == '\'')
	// 	check_cd_arguments_simple_quote(path[1]);
	// else
	//{
		i = 0;
		while (path[i] && path[i] != ' ')
			i++;
		if (path[i] == '\0')
			return (0);
		while (path[i] == ' ')
			i++;
		if (path[i] == '\0')
			return (0);
		else
			return (1);
	//}
}

void	cd(char *path)
{
	int		i;
	char	*new_path;

	i = 0;
	if (path[0] != '\0')
	{
		while (path[i] == ' ')
			i++;
		if (check_cd_arguments(&path[i]))
			ft_printf("minishell: cd: %s: too many arguments");
		if (chdir(path) == -1)
		{
			new_path = ft_strjoin("./", &path[i]);
			if (chdir(new_path) == -1)
			{
				ft_printf("minishell: cd: %s: No such file or directory", path);
				g_return_value = 1;
			}
			else
				g_return_value = 0;
			free(new_path);
		}
	}
	else
		g_return_value = 0;
}
