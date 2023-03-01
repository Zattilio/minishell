/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:58:49 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/01 13:47:56 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*get_tk_str_2(int tk_type)
{
	if (tk_type == TK_DINF)
		return ("DOUBLE_INF");
	if (tk_type == TK_DSUP)
		return ("DOUBLE_SUP");
	if (tk_type == TK_DOLLAR)
		return ("DOLLAR");
	if (tk_type == TK_SQUOTE)
		return ("SINGLE QUOTE");
	if (tk_type == TK_DQUOTE)
		return ("DOUBLE QUOTE");
	if (tk_type == TK_WILDCARD)
		return ("WILDCARD");
	if (tk_type == TK_EXEC)
		return ("EXEC");
	if (tk_type == TK_EOF)
		return ("TK_EOF");
	return ("");
}

char	*get_tk_str(int tk_type)
{
	if (tk_type == TK_WORD)
		return ("WORD");
	if (tk_type == TK_PIPE)
		return ("PIPE");
	if (tk_type == TK_AMP)
		return ("AMPERSAND");
	if (tk_type == TK_DPIPE)
		return ("DOUBLE_PIPE");
	if (tk_type == TK_DAMP)
		return ("DOUBLE_AMPERSAND");
	if (tk_type == TK_INF)
		return ("INF");
	if (tk_type == TK_SUP)
		return ("SUP");
	return (get_tk_str_2(tk_type));
}

static void	print_node_suite(t_node *root, int space)
{
	int	i;

	i = -1;
	print_space(space);
	ft_printf("| file_name : %s\n", root->file_name);
	print_space(space);
	ft_printf("| flags_open : %d\n", root->flags_open);
	print_space(space);
	ft_printf("| flags_open : %u\n", root->mode_open);
	print_space(space);
	ft_printf("| cmd : ");
	while (root->cmd && root->cmd[++i])
		ft_printf("%s ", root->cmd[i]);
	ft_printf("\n");
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
	ft_printf("| type  : %s\n", get_tk_str(root->token_type));
	print_space(space);
	ft_printf("| token : %s\n", root->token);
	print_node_suite(root, space);
	print_space(space);
	ft_printf("|--------------|\n");
	print2dutil(root->left, space);
}

void	print_ast(t_node *root)
{
	if (root == NULL)
		return ;
	print2dutil(root, 0);
}
