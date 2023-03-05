/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:50:34 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/05 03:47:27 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	exec_root(t_param *prm, t_node *root, char *env[])
{
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
		exec_pipe(prm, root, env);
	return (g_return_value);
}
