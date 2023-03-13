/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:40:18 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/13 02:10:26 by jlanza           ###   ########.fr       */
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

void	do_heredoc(t_pipe *args, t_fd *fd_list, t_node *node, int i)
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
	ft_lstprint(lst_str, node->file_name, fd_list, i);
	ft_lstclear(&lst_str, &free);
	(void)args;
}

/* void	do_heredoc(t_pipe *args, t_node *node, int i)
{
	ft_heredoc(args, args->fd_list, node, i);
} */
