/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:07:08 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/07 21:25:08 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	handle_sigint_parent(int sig)
{
	g_return_value = 130;
	(void)sig;
}

static void	handle_sigquit_parent(int sig)
{
	g_return_value = 131;
	(void)sig;
}

void	init_signal_parent(void)
{
	signal(SIGINT, &handle_sigint_parent);
	signal(SIGQUIT, &handle_sigquit_parent);
}

static void	handle_sigint_parent_during_exec(int sig)
{
	ft_printf("\n");
	g_return_value = 130;
	exit(130);
	(void)sig;
}

static void	handle_sigquit_parent_during_exec(int sig)
{
	g_return_value = 131;
	ft_printf("Quit (core dumped)\n");
	exit(131);
	(void)sig;
}

void	init_signal_parent_during_exec(void)
{
	signal(SIGINT, &handle_sigint_parent_during_exec);
	signal(SIGQUIT, &handle_sigquit_parent_during_exec);
}

static void	handle_sigint_parent_during_heredoc(int sig)
{
	ft_printf("^C\n");
	g_return_value = 130;
	close(0);
	exit(130);
	(void)sig;
}

void	init_signal_parent_during_heredoc(void)
{
	signal(SIGINT, &handle_sigint_parent_during_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint_heredoc(int)
{
	close(0);
	close(1);
	g_return_value = 130;
	//exit(130);
}

void	init_signal_heredoc(void)
{
	signal(SIGINT, &handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_sigint_child(int sig)
{
	exit (130);
	(void)sig;
}

static void	handle_sigquit_child(int sig)
{
	exit (131);
	(void)sig;
}

void	init_signal_child(void)
{
	signal(SIGINT, &handle_sigint_child);
	signal(SIGQUIT, &handle_sigquit_child);
}
