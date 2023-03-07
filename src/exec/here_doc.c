/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:47:07 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/07 18:31:14 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	ft_lstprint(t_list *lst, char *stop)
{
	while (lst && lst->content && (ft_strcmp((char *)(lst->content), stop)))
	{
		ft_putendl_fd((char *)(lst->content), 1);
		lst = lst->next;
	}
}

static void	ft_heredoc(t_pipe *args, t_fd *fd_list, t_node *node, int i)
{
	t_list	*lst_str;
	char	*str;

	lst_str = NULL;
	str = "";
	while (str && ft_strcmp(str, node->file_name))
	{
		str = readline("> ");
		ft_lstadd_back(&lst_str, ft_lstnew((void *)str));
	}
	if (!str)
		ft_printf("minishell: warning: here-document delimited by %s%s%s",
			"end-of-file (wanted '", node->file_name, "')\n");
	dup2(fd_list[i].fd[1], STDOUT_FILENO);
	ft_lstprint(lst_str, node->file_name);
	close_fd(args, fd_list);
	ft_lstclear(&lst_str, &free);
}

static void	fork_heredoc(t_pipe *args, t_node *node, int i)
{
	int	pid;
	int	stdin;

	pid = fork();
	if (pid == 0)
	{
		ft_heredoc(args, args->fd_list, node, i);
		free(args->pids);
		free(args->fd_list);
		empty_garbage(args->prm, -1);
		exit (0);
	}
	dup2(args->fd_list[i].fd[0], STDIN_FILENO);
	wait(NULL);
}

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

static int	redirection_heredoc(t_pipe *args, t_node *redir,
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

int	init_fork_heredoc(t_pipe *args, int *pids, t_fd *fd_list)
{
	int	i;

	i = 0;
	while (i < args->argc && is_parent_process(pids, i))
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			init_signal_heredoc();
			if (redirection_heredoc(args, args->argv[i]->redir, i, fd_list))
				ft_error(1, args, pids, fd_list);
			ft_error(0, args, pids, fd_list);
		}
		else
			waitpid(pids[i], NULL, 0);
		i++;
	}
	return (0);
}
