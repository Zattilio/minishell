/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:47:07 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/13 02:33:12 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fake_heredoc(t_node *node)
{
	char	*str;

	str = "";
	while (str && ft_strcmp(str, node->file_name))
	{
		str = readline("> ");
	}
	if (!str)
		ft_printf("minishell: warning: here-document delimited by %s%s%s",
			"end-of-file (wanted '", node->file_name, "')\n");
}

int	is_there_another_redir_in(t_node *redir)
{
	if (redir == NULL)
		return (0);
	if (redir->token_type == TK_INF || redir->token_type == TK_DINF)
		return (1);
	else
		return (is_there_another_redir_in(redir->left));
}

int	redirection_heredoc(t_pipe *args, t_node *redir,
	int i, t_fd *fd_list)
{
	if (redir == NULL)
		return (0);
	if (redir->token_type == TK_DINF)
	{
		if (is_there_another_redir_in(redir->left))
			fake_heredoc(redir);
		else
			do_heredoc(args, fd_list, redir, i);
	}
	return (redirection_heredoc(args, redir->left, i, fd_list));
}

int	init_heredoc(t_pipe *args, t_fd *fd_list)
{
	int	i;

	i = 0;
	while (i < args->argc)
	{
		init_signal_heredoc();
		redirection_heredoc(args, args->argv[i]->redir, i, fd_list);
		i++;
	}
	return (0);
}
