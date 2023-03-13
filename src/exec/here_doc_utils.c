/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:40:18 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/13 14:56:34 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstprint(t_list *lst, char *stop, t_fd *fd_list, int i)
{
	while (lst && lst->content && (ft_strcmp((char *)(lst->content), stop)))
	{
		ft_putendl_fd((char *)(lst->content), fd_list[i].fd[1]);
		lst = lst->next;
	}
}

void	stdin_closed_heredoc(t_pipe *args, t_fd *fd_list, t_list *lst_str)
{
	close_fd(args, fd_list);
	ft_lstclear(&lst_str, &free);
	empty_garbage(args->prm, -1);
	exit (130);
}

static int	is_fd_open(int fd)
{
	int	test;

	test = dup(fd);
	if (test == -1)
		return (0);
	close(test);
	return (1);
}

void	do_heredoc(t_pipe *args, t_fd *fd_list, t_node *node, int i)
{
	t_list	*lst_str;
	char	*str;

	lst_str = NULL;
	str = "";
	while (str && ft_strcmp(str, node->file_name))
	{
		str = readline("> ");
		ft_lstadd_back(&lst_str,
			ft_lstnew((void *)ft_strdup(substitute_heredoc(args->prm, str))));
		garbage_col(args->prm, args->prm->source.id, str);
	}
	if (is_fd_open(0))
	{
		if (!str)
			ft_printf("minishell: warning: here-document delimited by %s%s%s",
				"end-of-file (wanted '", node->file_name, "')\n");
		ft_lstprint(lst_str, node->file_name, fd_list, i);
	}
	else
		stdin_closed_heredoc(args, fd_list, lst_str);
	ft_lstclear(&lst_str, &free);
	(void)args;
}
