/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:32:12 by jlanza            #+#    #+#             */
/*   Updated: 2023/03/08 19:45:54 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

unsigned char	g_return_value = 0;

/*attention, ne pas utiliser l'enve du main*/
/*
int	main(int argc, char **argv, char **env)
{
	t_param	prm;
	t_node	*root;
	int		i;

	i = 1;
	if (argc < 2)
		return (1);
	ft_memset(&prm, 0, sizeof(t_param));
	clone_env(&prm, env);
	while (i < argc)
	{
		root = parse(&prm, argv[i]);
		print_ast(&prm, root);
		ft_printf("\n");
		i++;
	}
	empty_garbage(&prm, -1);
	return (0);
}*/

int	main(int argc, char *argv[], char *env[])
{
	char	*cmd;
	t_param	prm;
	t_node	*root;

	(void)argv;
	cmd = NULL;
	if (argc != 1)
		return (ft_printf_fd(2, "minishell: too many arguments"), 1);
	ft_memset(&prm, 0, sizeof(t_param));
	clone_env(&prm, env);
	print_minishell_title();
	while (1)
	{
		init_signal();
		readline_new_prompt(&cmd);
		if (cmd == NULL && ft_printf("exit\n"))
			break ;
		if (ft_strlen(cmd) > 0)
			add_history(cmd);
		root = parse(&prm, cmd);
		if (root != NULL)
			exec_root(&prm, root);
	}
	return (g_return_value);
}
