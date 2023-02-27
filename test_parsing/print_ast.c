/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:58:49 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 16:45:37 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_space(int space)
{
	int	i;

	i = 15;
	while (i < space)
	{
		ft_printf(" ");
		i++;
	}
}

static void	print2dutil(t_node *root, int space)
{
	if (root == NULL)
		return ;
	space += 15;
	print2dutil(root->right, space);
	print_space(space);
	ft_printf("|--------------|\n");
	print_space(space);
	ft_printf("| id    : %d\n", root->id);
	print_space(space);
	ft_printf("| type  : %d\n", root->token_type);
	print_space(space);
	ft_printf("| token : %s\n", root->token);
	print_space(space);
	ft_printf("|--------------|\n");
	print2dutil(root->left, space);
}

void	print_ast(t_node *root)
{
	print2dutil(root, 0);
}
/*
int	main(void)
{
	t_param	prm;
	int id = 0;
	int curseur = 0;
	t_node *root;

	ft_memset(&prm, 0, sizeof(t_param));
	root = make_node(&prm, 0, TK_WORD, "word");
	root->left = make_node(&prm, 1, TK_DOLLAR, "$");
	root->right = make_node(&prm, 2, TK_DQUOTE, "\"");
	print_ast(root);

	char line[] = "   ls | coucou  &    ";
	
	print_ast(get_token(&prm, &id, line, &curseur));
	print_ast(get_token(&prm, &id, line, &curseur));
	print_ast(get_token(&prm, &id, line, &curseur));
	print_ast(get_token(&prm, &id, line, &curseur));
	print_ast(get_token(&prm, &id, line, &curseur));
	empty_garbage(&prm);
	return (0);
}*/