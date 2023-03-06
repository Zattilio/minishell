/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:06:29 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/06 18:21:30 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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

/* int	clone_env(t_param *prm, char **env)
{
	int	i;
	int	pos;

	prm->env = ft_calloc_gc(prm, 0, get_nb_str(env) + 1, sizeof(char **));
	if (prm->env == NULL)
		return (1);
	i = -1;
	pos = -1;
	while (env && env[++i])
	{
		pos = get_pos_in_str(env[i], '=');
		if (pos != -1)
		{
			(prm->env)[i] = ft_calloc_gc(prm, 0, 3, sizeof(char *));
			if ((prm->env)[i] == NULL)
				return (1);
			((prm->env)[i])[0] = ft_substr(env[i], 0, pos);
			garbage_col(prm, 0, (prm->env)[i][0]);
			((prm->env)[i])[1] = ft_substr(env[i], pos + 1, ft_strlen(env[i]));
			garbage_col(prm, 0, (prm->env)[i][1]);
		}
	}
	return (0);
} */

char	*get_env_var(t_param *prm, char *name)
{
	int		i;
	size_t	len_name;
	size_t	len;
	size_t	pos;

	i = 0;
	len_name = ft_strlen(name);
	while (prm->env && prm->env[i])
	{
		len = len_name;
		pos = get_pos_in_str(prm->env[i], '=');
		if (pos > len_name)
			len = pos;
		if (ft_strncmp(prm->env[i], name, len) == 0)
			return (prm->env[i] + pos + 1);
		i++;
	}
	return ("");
}

void	print_env(t_param *prm)
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
}
