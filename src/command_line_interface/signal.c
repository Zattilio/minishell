/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:49:30 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/01 02:53:08 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_sigint(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

static void	handle_sigquit(int sig)
{
	ft_printf("\33[2K\r");
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	init_signal(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
}
