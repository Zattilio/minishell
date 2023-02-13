/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:35:55 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/13 16:38:27 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	is_path(char *str)
{
	if (str[0] == 'P'
		&& str[1] == 'A'
		&& str[2] == 'T'
		&& str[3] == 'H'
		&& str[4] == '=')
		return (1);
	return (0);
}

static char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(str1, str2);
	if (tmp == NULL)
		return (NULL);
	res = ft_strjoin(tmp, str3);
	free(tmp);
	return (res);
}

static char	**get_path_tab(t_arg *args)
{
	int	i;

	i = 0;
	while (args->env[i] != NULL && !is_path(args->env[i]))
		i++;
	if (!is_path(args->env[i]))
		return (NULL);
	return (ft_split(&(args->env[i][5]), ':'));
}

static int	test_exec_rights(char **path_cmd, char *path,
	char **path_tab, char **cmd)
{
	free_tab (path_tab);
	if (!access(path, X_OK))
	{
		*path_cmd = path;
		return (0);
	}
	return (permission_denied(cmd));
}

int	get_path_name(t_arg *args, char **path_cmd, char **cmd)
{
	int		i;
	char	**path_tab;
	char	*path;

	path_tab = get_path_tab(args);
	if (path_tab == NULL && !access(cmd[0], F_OK))
		return (test_exec_rights(path_cmd, cmd[0], path_tab, cmd));
	if (path_tab == NULL)
		return (command_not_found(path_tab, cmd));
	i = 0;
	while (path_tab[i] != NULL)
	{
		path = ft_strjoin3(path_tab[i], "/", cmd[0]);
		if (path == NULL)
			return (error_ft_strjoin3(path_tab, cmd));
		if (!access(path, F_OK))
			return (test_exec_rights(path_cmd, path, path_tab, cmd));
		free(path);
		i++;
	}
	if (!access(cmd[0], F_OK))
		return (test_exec_rights(path_cmd, cmd[0], path_tab, cmd));
	return (command_not_found(path_tab, cmd));
}
