/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_n_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:15:18 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/13 15:13:29 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	no_other_redir_in(t_node *redir)
{
	if (redir == NULL)
		return (1);
	if (redir->token_type == TK_INF || redir->token_type == TK_DINF)
		return (0);
	else
		return (no_other_redir_in(redir->left));
}

int	no_other_redir_out(t_node *redir)
{
	if (redir == NULL)
		return (1);
	if (redir->token_type == TK_SUP || redir->token_type == TK_DSUP)
		return (0);
	else
		return (no_other_redir_out(redir->left));
}

int	redir_in(t_node *redir)
{
	int	fd_input;

	fd_input = open(redir->file_name, redir->flags_open, redir->mode_open);
	if (fd_input == -1)
	{
		if (!access(redir->file_name, F_OK))
			ft_put3str_fd("minishell: ", redir->file_name,
				": Permission denied\n", 2);
		else
			ft_put3str_fd("minishell: ", redir->file_name,
				": No such file or directory\n", 2);
		return (1);
	}
	if (no_other_redir_in(redir->left))
		dup2(fd_input, 0);
	close(fd_input);
	return (0);
}

int	redir_out(t_node *redir)
{
	int	fd_output;

	fd_output = open(redir->file_name, redir->flags_open, redir->mode_open);
	if (fd_output == -1)
	{
		ft_put3str_fd("minishell: ", redir->file_name,
			": Permission denied\n", 2);
		return (1);
	}
	if (no_other_redir_out(redir->left))
		dup2(fd_output, 1);
	close(fd_output);
	return (0);
}

static int	redir_heredoc(t_fd *fd_list, int i)
{
	dup2(fd_list[i].fd[0], 0);
	return (0);
}

int	redirection(t_pipe *args, t_node *redir, int i, t_fd *fd_list)
{
	if (redir == NULL)
		return (0);
	if (redir->token_type == TK_INF)
	{
		if (redir_in(redir))
			return (1);
	}
	if (redir->token_type == TK_DINF && no_other_redir_in(redir->left))
		redir_heredoc(fd_list, i);
	if (redir->token_type == TK_SUP || redir->token_type == TK_DSUP)
	{
		if (redir_out(redir))
			return (1);
	}
	if (i != 0 && redir->token_type == TK_EXEC
		&& no_other_redir_in(redir->redir))
		dup2(fd_list[i].fd[0], 0);
	if (i + 1 != args->argc && redir->token_type == TK_EXEC
		&& no_other_redir_out(redir->redir))
		dup2(fd_list[i + 1].fd[1], 1);
	return (redirection(args, redir->left, i, fd_list));
}

int	execute_all_cmds(t_pipe *args, int *pids, t_fd *fd_list)
{
	int	i;

	init_signal_parent_during_exec();
	i = 0;
	while (i < args->argc && is_parent_process(pids, i))
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			init_signal_child();
			if (redirection(args, args->argv[i]->redir, i, fd_list))
				ft_error(1, args, fd_list);
			close_fd(args, fd_list);
			ft_error(execute_cmd(args, i), args, fd_list);
		}
		if (pids[i] < 0)
			ft_error(5, args, fd_list);
		i++;
	}
	return (0);
}
