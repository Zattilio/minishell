/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:47:07 by jlanza            #+#    #+#             */
/*   Updated: 2023/02/13 16:38:27 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_heredoc(t_arg *args)
{
	return (!ft_strncmp("here_doc", args->argv[1],
			ft_strlen(args->argv[1]) + 1));
}

void	fork_heredoc(t_arg *args, int *pids, t_fd *fd_list)
{
	if (check_heredoc(args))
	{
		pids[0] = fork();
		if (pids[0] == 0)
		{
			ft_heredoc(args, fd_list);
			free(pids);
			free(fd_list);
			free(args);
			exit (0);
		}
	}
	wait(NULL);
}

static void	ft_put_heredoc(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->argc - 5)
	{
		ft_printf("pipe ");
		i++;
	}
	ft_printf("heredoc> ");
}

static void	ft_lstprint(t_list *lst, char *stop)
{
	while (ft_strncmp((char *)(lst->content), stop, ft_strlen(stop))
		|| ft_strlen(lst->content) != ft_strlen(stop) + 1)
	{
		ft_putstr_fd((char *)(lst->content), 1);
		lst = lst->next;
	}
}

void	ft_heredoc(t_arg *args, t_fd *fd_list)
{
	t_list	*lst_str;
	char	*str;

	lst_str = NULL;
	while (!lst_str || (ft_strncmp(str, args->argv[2], ft_strlen(args->argv[2]))
			|| ft_strlen(str) != ft_strlen(args->argv[2]) + 1))
	{
		ft_put_heredoc(args);
		str = get_next_line(0);
		ft_lstadd_back(&lst_str, ft_lstnew((void *)str));
	}
	dup2(fd_list[0].fd[1], STDOUT_FILENO);
	ft_lstprint(lst_str, args->argv[2]);
	close_fd(args, fd_list);
	ft_lstclear(&lst_str, &free);
}
