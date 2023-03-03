/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:00:06 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/03 17:44:34 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/minishell.h"

static int	ft_argc(t_node *root)
{
	int	n;

	n = 0;
	while (root->token_type != TK_INF && root->token_type != TK_SUP
		&& root->token_type != TK_DINF && root->token_type != TK_DSUP
		&& root->token_type != TK_EXEC)
	{
		root = root->right;
		n++;
	}
	return (n + 4);
}

static void	init_s_pipe(t_pipe *pipe, t_node *root, char *env[], t_param *prm)
{
	t_node	*right_parent;
	t_node	*left_child;
	int		i;

	pipe->argc = ft_argc(root);
	pipe->env = env;
	pipe->prm = prm;
	pipe->argv = ft_calloc_gc(prm, prm->source.id,
			pipe->argc + 1, sizeof(t_node *));
	right_parent = root;
	i = 0;
	while (right_parent)
	{
		left_child = right_parent;
		while (left_child->left)
		{
			left_child = left_child->left;
		}
		pipe->argv[i] = left_child;
		i++;
		right_parent = right_parent->right;
	}
}

int	exec_pipe(t_param *prm, t_node *root, char *env[])
{
	// t_fd	*fd_list;
	t_pipe	pipe;
	// int		*pids;
	// int		status;

	init_s_pipe(&pipe, root, env, prm);
	print_ast(root);
/* 	init_pipex(root, &pids, &fd_list);
	init_pipes(root, pids, fd_list);
	fork_heredoc(root, pids, fd_list);
	init_fork(root, pids, fd_list);
	if (pids[0] == 0)
		ft_error(execute_first_cmd(root, fd_list), root, pids, fd_list);
	execute_middle_cmd(root, pids, fd_list);
	if (pids[ft_argc(root) - 4] == 0)
		ft_error(execute_last_cmd(root, fd_list), root, pids, fd_list);
	close_fd(root, fd_list);
	ft_wait(root, pids);
	waitpid(pids[ft_argc(root) - 4], &status, 0);
	free(pids);
	free(fd_list);
	return (WEXITSTATUS(status));
	(void) */
	return (0);
}
