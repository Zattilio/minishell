/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:24:21 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/10 13:39:18 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint_parent(int sig)
{
	g_return_value = 130;
	(void)sig;
}

void	handle_sigquit_parent(int sig)
{
	g_return_value = 131;
	(void)sig;
}

void	reset_ret_val_and_init_signal_parent(void)
{
	g_return_value = 0;
	signal(SIGINT, &handle_sigint_parent);
	signal(SIGQUIT, &handle_sigquit_parent);
}
