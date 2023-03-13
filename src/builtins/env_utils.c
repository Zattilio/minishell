/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:20:08 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/13 17:07:26 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_error_print_env(int ret_val)
{
	write(2, "minishell: env: write error: No space left on device\n",
		ft_strlen("minishell: env: write error: No space left on device\n"));
	return (ret_val);
}

int	print_env(t_param *prm)
{
	int	i;

	i = 0;
	if (prm->env == NULL && write(1, "\n", ft_strlen("\n")) == -1)
		return (ft_error_print_env(1));
	while (prm->env[i])
	{
		if (write(1, prm->env[i], ft_strlen(prm->env[i])) == -1)
			return (ft_error_print_env(1));
		if (write(1, "\n", ft_strlen("\n")) == -1)
			return (ft_error_print_env(1));
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
