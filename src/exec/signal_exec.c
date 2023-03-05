/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:07:08 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/05 00:23:01 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	handle_sigint_parent(int sig)
{
	g_return_value = sig;
	printf("\n");
}

static void	handle_sigquit_parent(int sig)
{
	g_return_value = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}

void	init_signal_parent(void)
{
	signal(SIGINT, &handle_sigint_parent);
	signal(SIGQUIT, &handle_sigquit_parent);
}

static void	handle_sigint_child(int sig)
{
	printf("sigint child\n");
	exit (g_return_value);
	(void)sig;
}

static void	handle_sigquit_child(int sig)
{
	printf("sigquit child\n");
	exit (g_return_value);
	(void)sig;
}

void	init_signal_child(void)
{
	signal(SIGINT, &handle_sigint_child);
	signal(SIGQUIT, &handle_sigquit_child);
}
