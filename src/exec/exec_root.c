/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:50:34 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/05 01:09:37 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	exec_root(t_param *prm, t_node *root, char *env[])
{
	if (root->token_type == TK_DAMP)
	{
		g_return_value = exec_root(prm, root->left, env);
		if (g_return_value == 0)
			g_return_value = exec_root(prm, root->right, env);
	}
	else if (root->token_type == TK_DPIPE)
	{
		g_return_value = exec_root(prm, root->left, env);
		if (g_return_value != 0)
			g_return_value = exec_root(prm, root->right, env);
	}
	else
		g_return_value = exec_pipe(prm, root, env);
	return (g_return_value);
}
