/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:20:08 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 15:14:21 by mbocquel         ###   ########.fr       */
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
