/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:49:30 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/05 03:11:28 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Version that display ^C in shell
/* static void	handle_sigint(int sig)
{
	g_return_value = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_printf("\33[2K\r");
	printf_new_prompt();
	(void)sig;
} */
static void	handle_sigint(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	ft_printf("\33[2K\r");
	printf_new_prompt();
	g_return_value = 131;
	ft_printf("  \b \b\b \b\n");
	printf_new_prompt();
	(void)sig;
}
/* static void	handle_sigquit(int sig)
{
	ft_printf("\33[2K\r");
	rl_on_new_line();
	rl_redisplay();
	ft_printf("\33[2K\r");
	printf_new_prompt();
	(void)sig;
} */

void	init_signal(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
