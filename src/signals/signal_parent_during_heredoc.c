/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent_during_heredoc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:26:41 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 19:37:25 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_sigint_parent_during_heredoc(int sig)
{
	ft_printf("^C\n");
	g_return_value = 130;
	(void)sig;
}

static void	init_signal_parent_during_heredoc(void)
{
	signal(SIGINT, &handle_sigint_parent_during_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
