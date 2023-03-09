/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:30:00 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/09 10:09:12 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	close(0);
	close(1);
	g_return_value = 130;
}

void	init_signal_heredoc(void)
{
	signal(SIGINT, &handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
