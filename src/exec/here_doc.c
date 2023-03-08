/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:47:07 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 19:41:15 by jlanza           ###   ########.fr       */
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

int	is_there_another_heredoc(t_node *node)
{
	while (node->left)
	{
		node = node->left;
		if (node->token_type == TK_DINF)
			return (1);
	}
	return (0);
}

int	redirection_heredoc(t_pipe *args, t_node *redir,
	int i, t_fd *fd_list)
{
	if (redir == NULL)
		return (0);
	if (redir->token_type == TK_DINF)
	{
		if (is_there_another_heredoc(redir))
			fake_heredoc(redir);
		else
			fork_heredoc(args, redir, i);
	}
	return (redirection_heredoc(args, redir->left, i, fd_list));
}

void	clean_heredoc(t_pipe *args, t_fd *fd_list)
{
	close_fd(args, fd_list);
	empty_garbage(args->prm, -1);
	exit (131);
}

int	init_fork_heredoc(t_pipe *args, int *pids, t_fd *fd_list)
{
	int	i;
	int	status;

	i = 0;
	while (i < args->argc && is_parent_process(pids, i))
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			init_signal_heredoc();
			if (redirection_heredoc(args, args->argv[i]->redir, i, fd_list))
				ft_error(1, args, fd_list);
			ft_error(0, args, fd_list);
		}
		else
		{
			waitpid(pids[i], &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == 131)
				clean_heredoc(args, fd_list);
		}
		i++;
	}
	return (0);
}
