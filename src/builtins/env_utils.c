/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:20:08 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 19:38:48 by jlanza           ###   ########.fr       */
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

int	clone_env(t_param *prm, char **env)
{
	int	i;

	prm->env = ft_calloc_gc(prm, 0, get_nb_str(env) + 1, sizeof(char *));
	if (prm->env == NULL)
		return (1);
	i = -1;
	while (env && env[++i])
	{
		(prm->env)[i] = ft_strdup_gc(prm, 0, env[i]);
		if ((prm->env)[i] == NULL)
			return (1);
	}
	return (0);
}
