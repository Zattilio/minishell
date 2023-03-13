/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:20:08 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/13 11:54:53 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_env(t_param *prm)
{
	int	i;

	i = 0;
	if (prm->env == NULL)
		ft_printf("\n");
	while (prm->env[i])
	{
		ft_printf("%s\n", prm->env[i]);
		i++;
	}
	return (0);
}

void	garbage_env(t_param *prm)
{
	int	i;

	i = -1;
	while (prm->env && prm->env[++i])
		remove_from_garb(prm, prm->env[i]);
	remove_from_garb(prm, prm->env);
}

int	increment_shlvl(t_param *prm)
{
	char	*new_level;
	char	*new_shlvl;

	new_level = ft_itoa(ft_atoi(get_env_var(prm, "SHLVL")) + 1);
	if (new_level == NULL)
		return (1);
	unset_env(prm, "SHLVL");
	new_shlvl = ft_strjoin_gc(prm, 0, "SHLVL=", new_level);
	free(new_level);
	if (new_shlvl == NULL)
		return (1);
	export_env(prm, new_shlvl);
	return (0);
}

void	clone_env(t_param *prm, char **env)
{
	int	i;

	prm->env = ft_calloc_gc(prm, 0, get_nb_str(env) + 1, sizeof(char *));
	if (prm->env == NULL)
	{
		empty_garbage(prm, -1);
		exit (1);
	}
	i = -1;
	while (env && env[++i])
	{
		(prm->env)[i] = ft_strdup_gc(prm, 0, env[i]);
		if ((prm->env)[i] == NULL)
		{
			empty_garbage(prm, -1);
			exit (1);
		}
	}
	if (increment_shlvl(prm))
	{
		empty_garbage(prm, -1);
		exit (1);
	}
}

int	check_valid_export(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = pos_str(str, '=');
	if (len == -1 && str)
		len = ft_strlen(str);
	while (i < len)
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (2);
		if (i == 0 && ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
