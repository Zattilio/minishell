/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:50:34 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 18:02:45 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*int	exec_root(t_param *prm, t_node *root, char *env[])
{
	int	pipe_pid;

	init_signal_parent();
	if (root->token_type == TK_DAMP)
	{
		exec_root(prm, root->left, env);
		if (g_return_value == 0)
			exec_root(prm, root->right, env);
	}
	else if (root->token_type == TK_DPIPE)
	{
		exec_root(prm, root->left, env);
		if (g_return_value != 0)
			exec_root(prm, root->right, env);
	}
	else
	{
		pipe_pid = fork();
		if (pipe_pid == 0)
		{
			init_signal_parent_during_heredoc();
			exec_pipe(prm, root, env);
		}
		else
			waitpid(pipe_pid, NULL, 0);
	}
	return (g_return_value);
}
*/
int	exec_root(t_param *prm, t_node *root)
{
	int	pipe_pid;

	init_signal_parent();
	pipe_pid = fork();
	if (pipe_pid == 0)
	{
		init_signal_parent_during_heredoc();
		exec_pipe(prm, root);
	}
	else
		waitpid(pipe_pid, NULL, 0);
	//exec cd exit, export et unset, si on a pas de pipe et que c'est la fonction a faire. 
	return (g_return_value);
}
