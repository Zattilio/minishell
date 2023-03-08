/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_n_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:15:18 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 18:03:06 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
int	execute_first_cmd(t_pipe *args, t_fd *fd_list)
{
	int		fd_input;

	if (!check_heredoc(args))
	{
		dup2(fd_list[0].fd[1], STDOUT_FILENO);
		close_fd(args, fd_list);
		fd_input = open(args->argv[1], O_RDONLY, 00600);
		if (fd_input == -1)
		{
			if (!access(args->argv[1], F_OK))
				ft_put3str_fd("minishell: ", args->argv[1],
					": Permission denied\n", 2);
			else
				ft_put3str_fd("minishell: ", args->argv[1],
					": No such file or directory\n", 2);
			return (1);
		}
		dup2(fd_input, 0);
		close(fd_input);
		return (execute_cmd(args, 2));
	}
	return (0);
}*/

/*
int	execute_last_cmd(t_pipe *args, t_fd *fd_list)
{
	int	fd_output;

	dup2(fd_list[args->argc - 5].fd[0], STDIN_FILENO);
	close_fd(args, fd_list);
	if (!check_heredoc(args))
		fd_output = open(args->argv[args->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 00644);
	else
		fd_output = open(args->argv[args->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 00644);
	if (fd_output == -1)
	{
		ft_put3str_fd("minishell: ", args->argv[args->argc - 1],
			": Permission denied\n", 2);
		return (1);
	}
	dup2(fd_output, 1);
	close(fd_output);
	return (execute_cmd(args, args->argc - 1 - 1));
}
 */

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
	if (i != 0)
		dup2(fd_list[i].fd[0], 0);
	if (i + 1 != args->argc)
		dup2(fd_list[i + 1].fd[1], 1);
	if (redir == NULL)
		return (0);
	if (redir->token_type == TK_INF)
	{
		if (redir_in(redir))
			return (1);
	}
	if (redir->token_type == TK_SUP || redir->token_type == TK_DSUP)
	{
		if (redir_out(redir))
			return (1);
	}
	if (redir->token_type == TK_DINF && redir->left->token_type == TK_EXEC)
		return (redir_heredoc(fd_list, i));
	return (redirection(args, redir->left, i, fd_list));
}

int	execute_all_cmds(t_pipe *args, int *pids, t_fd *fd_list)
{
	int	i;

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
