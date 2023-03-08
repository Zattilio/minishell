/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:57:47 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/02 16:51:40 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(char *arg[], char *env[])
{
	char	*working_directory;

	working_directory = getcwd(NULL, 0);
	ft_printf("%s\n", working_directory);
	free(working_directory);
	(void)arg;
	(void)env;
}
