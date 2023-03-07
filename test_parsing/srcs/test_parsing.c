/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:29:46 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/07 18:31:00 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
}
/*
int	main(int argc, char **argv, char **env)
{
	t_param	prm;

	(void)argc;
	(void)argv;
	ft_memset(&prm, 0, sizeof(t_param));
	clone_env(&prm, env);
	ft_printf("	environnement \n");
	print_env(&prm);
	ft_printf("\n\n	add env \n\n");
	export_env(&prm, "COUCOUYOUYOU");
	ft_printf("	environnement \n");
	print_env(&prm);
	ft_printf("\n\n	unset env \n\n");
	unset_env(&prm, "COUCOU");
	ft_printf("	environnement \n");
	print_env(&prm);
	empty_garbage(&prm, -1);
	return (0);
}
*/