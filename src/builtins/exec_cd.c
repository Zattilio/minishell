/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:40:40 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/09 15:40:20 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_pwd_env(t_param *prm, char *old_pwd)
{
	char	*new_pwd;
	int		ret;

	ret = 0;
	garbage_col(prm, prm->source.id, old_pwd);
	new_pwd = getcwd(NULL, 0);
	garbage_col(prm, prm->source.id, new_pwd);
	old_pwd = ft_strjoin_gc(prm, 0, "OLDPWD=", old_pwd);
	new_pwd = ft_strjoin_gc(prm, 0, "PWD=", new_pwd);
	ret += unset_env(prm, "OLDPWD");
	ret += unset_env(prm, "PWD");
	ret += export_env(prm, old_pwd);
	ret += export_env(prm, new_pwd);
	return (ret);
}

int	exec_cd(t_param *prm, char *arg[])
{
	char	*new_path;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (get_nb_str(arg) != 2)
	{
		ft_printf("minishell: cd: wrong number of arguments\n");
		g_return_value = 1;
		return (0);
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
	if (change_pwd_env(prm, old_pwd))
		return (1);
	return (0);
}
