/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent_during_exec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:25:13 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/13 04:07:33 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	handle_sigint_parent_during_exec(int sig)
{
	ft_printf("\n");
	g_return_value = 130;
	(void)sig;
}

void	handle_sigquit_parent_during_exec(int sig)
{
	g_return_value = 131;
	ft_printf("Quit (core dumped)\n");
	(void)sig;
} */

void	init_signal_parent_during_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
