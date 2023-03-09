/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:07:08 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/09 10:09:06 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint_child(int sig)
{
	exit (130);
	(void)sig;
}

void	handle_sigquit_child(int sig)
{
	exit (131);
	(void)sig;
}

void	init_signal_child(void)
{
	signal(SIGINT, &handle_sigint_child);
	signal(SIGQUIT, &handle_sigquit_child);
}
