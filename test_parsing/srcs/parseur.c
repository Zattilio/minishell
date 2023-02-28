/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:31:33 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/28 18:22:31 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The parser check that the syntax of the user command is valid. It then 
generates an Abstract Syntax Tree (AST) that will be use for the next step :
the execution.*/

/*Plusieurs approches de parsing ; Top Down Parsing et Bottom up parsing.
 mais aussi Recursive descent parser
 */
#include "parsing.h"

t_node *parsing(t_param *prm)
{
	char	*token;
	t_node	*root;
	
	token = get_token(prm);
	root = parsing_prog(prm, token);
	if (get_token_type(pick_next_token(prm)) != TK_EOF)
		return (NULL);
	return (root);
}

t_node *parsing_line(t_param *prm, char *token)
{
	
}

t_node	*make_pipe_node(t_param *prm, t_node *left, t_node *right)
{
	t_node	*node;

	node = ft_malloc_gc(prm, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->id = prm->id;
	node->token_type = TK_PIPE;
	node->token = "|";
	node->left = left;
	node->right = right;
	node->parent = NULL;
	return (node);
}

/* voir https://youtu.be/ZjzMdsTWF0U?t=1464 */

t_node *parsing_pipe(t_param *prm)
{
	t_node *node;

	node = parse_exec(prm);
	if (get_token_type(pick_next_token(prm)) == TK_PIPE)
	{
		get_token(prm);
		node = make_pipe_node(prm, node, parsing_pipe(prm));
	}
	return (node);
}

/*il faut une fonction pour chaque truc de la grammaire. */