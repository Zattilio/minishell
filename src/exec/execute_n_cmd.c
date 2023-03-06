/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_n_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:15:18 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/06 17:17:45 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

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

void	redir_in(t_node *node)
{
/* 	int	fd_input;

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
	close(fd_input); */
	(void)node;
}

void	redir_out(t_node *node)
{
	(void)node;
}

void	redir_double_out(t_node *node)
{
	(void)node;
}

void	redir_heredoc(t_node *node)
{
	(void)node;
}


void	redirection(t_pipe *args, t_node *node, int i, t_fd *fd_list)
{
	if (i != 0)
		dup2(fd_list[i - 1].fd[0], 0);
	if (i + 1 != args->argc)
		dup2(fd_list[i].fd[1], 1);
	if (node == NULL)
		return ;
	if (node->token_type == TK_INF)
		redir_in(node);
	if (node->token_type == TK_SUP)
		redir_out(node);
	if (node->token_type == TK_DINF)
		redir_heredoc(node);
	if (node->token_type == TK_DSUP)
		redir_double_out(node);
	redirection(args, node->left, i, fd_list);
}

void	execute_all_cmds(t_pipe *args, int *pids, t_fd *fd_list)
{
	int	i;

	i = 0;
	init_signal_parent();
	while (i < args->argc)
	{
		if (pids[i] == 0)
		{
			init_signal_child();
			redirection(args, args->argv[i]->redir, i, fd_list);
			close_fd(args, fd_list);
			ft_error(execute_cmd(args, i), args, pids, fd_list);
		}
		i++;
	}
}
