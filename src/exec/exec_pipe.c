/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:00:06 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/09 16:46:05 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (n + 1);
}

static void	init_s_pipe(t_pipe *pipe, t_node *root, t_param *prm)
{
	t_node	*right_parent;
	t_node	*left_child;
	int		i;

	pipe->argc = ft_argc(root);
	pipe->prm = prm;
	pipe->root = root;
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
		pipe->argv[i]->redir = right_parent;
		i++;
		right_parent = right_parent->right;
	}
	init_pipex(pipe, &pipe->pids, &pipe->fd_list);
}

/* static void	print_pipe(t_pipe *root)
{
	int		i;

	i = 0;
	while (root->argv[i])
	{
		print_ast(root->argv[i]);
		i++;
	}
	if (root->argv[i] == NULL)
		printf("end\n");
	printf("argc = %d\n", root->argc);
} */

int	exec_pipe(t_param *prm, t_node *root)
{
	t_pipe	args;
	int		status;

	init_s_pipe(&args, root, prm);
	init_pipes(&args, args.fd_list);
	if (root->token_type == TK_EXEC && root->cmd == NULL)
	{
		g_return_value = 0;
		return (0);
	}
	init_fork_heredoc(&args, args.pids, args.fd_list);
	init_signal_parent_during_exec();
	execute_all_cmds(&args, args.pids, args.fd_list);
	close_fd(&args, args.fd_list);
	ft_wait(&args, args.pids);
	waitpid(args.pids[args.argc], &status, 0);
	if (WIFSIGNALED(status))
		g_return_value = WTERMSIG(status);
	else if (WIFEXITED(status))
		g_return_value = WEXITSTATUS(status);
	empty_garbage(prm, -1);
	exit (g_return_value);
}
