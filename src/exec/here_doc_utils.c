/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:40:18 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 19:41:10 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstprint(t_list *lst, char *stop)
{
	while (lst && lst->content && (ft_strcmp((char *)(lst->content), stop)))
	{
		ft_putendl_fd((char *)(lst->content), 1);
		lst = lst->next;
	}
}

void	ft_heredoc(t_pipe *args, t_fd *fd_list, t_node *node, int i)
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

void	fork_heredoc(t_pipe *args, t_node *node, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_heredoc(args, args->fd_list, node, i);
		empty_garbage(args->prm, -1);
		exit (0);
	}
	dup2(args->fd_list[i].fd[0], STDIN_FILENO);
	wait(NULL);
}
