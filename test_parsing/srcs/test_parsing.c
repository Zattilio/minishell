/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:29:46 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/03 17:52:15 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Test de la recuperation des valeurs d'environnement */
/*
int	main(int argc, char **argv, char **env)
{
	t_param	prm;
	(void)argc;
	(void)argv;
	ft_memset(&prm, 0, sizeof(t_param));
	clone_env(&prm, env);
	ft_printf("mon login = %s\n\n",get_env_var(&prm, "USER"));
	print_env(&prm);
	empty_garbage(&prm,-1);
	return (0);
}
*/
/*
//main pour tester la prise en compte des quote
int	main(int argc, char **argv, char **env)
{
	t_param	prm;
	char	*word = NULL;
	
	ft_memset(&prm, 0, sizeof(t_param));
	prm.source.id = 1;
	prm.source.line = "ls \'coucou $ * | < >A\' > in";
	if (prm.source.line)
		prm.source.line_size = ft_strlen(prm.source.line);
	clone_env(&prm, env);
	while (peek_tk(&prm) != TK_EOF)
	{
		printf("prochain tk de type %d\n", peek_tk(&prm));
		if (peek_tk(&prm) == TK_WORD || peek_tk(&prm) == TK_SQUOTE)
		{
			word = get_word(&prm);
			printf("%s\n",word);
		}
		else
			get_token(&prm);
	}
	empty_garbage(&prm, prm.source.id);
	return (0);
}*/

int	main(int argc, char **argv)
{
	t_param	prm;
	t_node	*node;
	//(void)argv;
	//(void)argc;
	if (argc != 2)
		return (1);
	ft_memset(&prm, 0, sizeof(t_param));
	prm.source.id = 0;
	prm.source.line = ft_strdup_gc(&prm, argv[1]);
	//prm.source.line = ft_strdup_gc(&prm, "\'ls \" $ |     \"  \'y");
	if (prm.source.line)
		prm.source.line_size = ft_strlen(prm.source.line);
	//printf("%zu\n", prm.source.line_size);
	node = parse_pipe(&prm);
	print_ast(node);
	empty_garbage(&prm, prm.source.id);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	t_param	prm;
	t_node	*node;
	char	*token;
	int		id;

	id = 0;
	if (argc != 2)
		return (1);
	ft_memset(&prm, 0, sizeof(t_param));
	prm.source.line = ft_strdup(argv[1]);
	prm.source.id = 1;
	if (prm.source.line)
		prm.source.line_size = ft_strlen(prm.source.line);
	while (1)
	{
		token = get_token(&prm);
		node = make_node(&prm, ++id, get_t_token(token), token);
		print_ast(node);
		if (node->token_type == TK_EOF)
			break ;
	}
	print_garbage(&prm);
	empty_garbage(&prm, prm.source.id);
	print_garbage(&prm);
	free(prm.source.line);
	return (0);
}*/