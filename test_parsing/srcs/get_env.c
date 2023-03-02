/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:06:29 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/02 16:11:16 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	clone_env(t_param *prm, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	env
}

char	*ft_get_env(t_param *prm, char *name);
