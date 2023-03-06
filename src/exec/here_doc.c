/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:47:07 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/06 21:04:19 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/* int	has_not_delimiter(t_list *lst, char *stop)
{
	while (lst)
	{
		if (ft_strncmp((char *)(lst->content), stop, ft_strlen(stop))
			|| ft_strlen(lst->content) != ft_strlen(stop) + 1)
			return (0);
		lst = lst->next;
	}
	return (1);
} */

static void	ft_lstprint(t_list *lst, char *stop)
{
	while (lst && (ft_strncmp((char *)(lst->content), stop, ft_strlen(stop))
		|| ft_strlen(lst->content) != ft_strlen(stop) + 1))
	{
		ft_putstr_fd((char *)(lst->content), 1);
		lst = lst->next;
	}
}

static void	ft_heredoc(t_pipe *args, t_fd *fd_list, t_node *node, int i)
{
	t_list	*lst_str;
	char	*str;

	lst_str = NULL;
	str = (void*)node;
	while (str && (!lst_str || (ft_strncmp(str, node->file_name, ft_strlen(node->file_name))
			|| ft_strlen(str) != ft_strlen(node->file_name) + 1)))
	{
		ft_printf("> ");
		str = get_next_line(0);
		if (str != NULL)
			ft_lstadd_back(&lst_str, ft_lstnew((void *)str));
	}
	if (!str)
		ft_printf("minishell: warning: here-document delimited by end-of-file (wanted '%s')\n", node->file_name);
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
		free(args->pids);
		free(args->fd_list);
		exit (0);
	}
	dup2(args->fd_list[i].fd[0], 0);
	wait(NULL);
}
