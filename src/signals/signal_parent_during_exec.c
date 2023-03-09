/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent_during_exec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:25:13 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/09 15:47:29 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_sigint_parent_during_exec(int sig)
{
	ft_printf("\n");
	g_return_value = 130;
	(void)sig;
}

static void	handle_sigquit_parent_during_exec(int sig)
{
	g_return_value = 131;
	ft_printf("Quit (core dumped)\n");
	(void)sig;
}

void	init_signal_parent_during_exec(void)
{
	signal(SIGINT, &handle_sigint_parent_during_exec);
	signal(SIGQUIT, &handle_sigquit_parent_during_exec);
}
