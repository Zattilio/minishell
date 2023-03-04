/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 06:52:28 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/04 16:52:04 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/* static int	check_only_spaces(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
} */

/* static char	**init_space_cmd(char *cmd)
{
	char	**cmd_tab;

	cmd_tab = ft_calloc(2, sizeof(*cmd_tab));
	cmd_tab[0] = ft_strdup(cmd);
	return (cmd_tab);
} */

int	execute_cmd(t_pipe *args, int n_cmd)
{
	char	**cmd1;
	char	*path_cmd1;
	int		return_value;

	//if (!check_only_spaces(args->argv[n_cmd]->cmd[0]))
		//cmd1 = init_space_cmd(args->argv[n_cmd]->cmd);
	//else
	cmd1 = args->argv[n_cmd]->cmd;
	ft_printf("%s\n", cmd1[0]);
	if (cmd1 == NULL)
		return (1);
	return_value = get_path_name(args, &path_cmd1, cmd1);
	if (return_value != 0)
		return (return_value);
	if (execve(path_cmd1, cmd1, args->env) == -1)
	{
		free(path_cmd1);
		free_tab(cmd1);
	}
	return (6);
}
