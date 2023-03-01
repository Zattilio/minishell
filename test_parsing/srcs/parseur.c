/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:31:33 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/01 14:00:38 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The parser check that the syntax of the user command is valid. It then 
generates an Abstract Syntax Tree (AST) that will be use for the next step :
the execution.*/

/*Plusieurs approches de parsing ; Top Down Parsing et Bottom up parsing.
 mais aussi Recursive descent parser
 */
#include "parsing.h"

t_node	*make_pipe_node(t_param *prm, t_node *left, t_node *right)
{
	t_node	*node;

	node = ft_malloc_gc(prm, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->id = prm->id;
	node->token_type = TK_PIPE;
	node->token = "|";
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*make_redir_node(t_param *prm, t_node *left,
	int token_type, char *file_name)
{
	t_node	*node;

	node = ft_malloc_gc(prm, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->id = prm->id;
	node->token_type = token_type;
	node->token = get_tk_str(token_type);
	node->mode_open = 00644;
	if (token_type == TK_INF)
		node->flags_open = O_RDONLY;
	else if (token_type == TK_SUP)
		node->flags_open = O_WRONLY | O_CREAT | O_TRUNC;
	else if (token_type == TK_DSUP)
		node->flags_open = O_WRONLY | O_CREAT | O_APPEND;
	if (token_type == TK_INF)
		node->mode_open = 00600;
	node->file_name = file_name;
	node->left = left;
	return (node);
}

t_node	*make_exec_node(t_param *prm, char **cmd)
{
	t_node	*node;

	node = ft_malloc_gc(prm, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->id = prm->id;
	node->token_type = TK_EXEC;
	node->token = get_tk_str(TK_EXEC);
	node->cmd = cmd;
	return (node);
}

t_node	*parsing(t_param *prm)
{
	t_node	*root;

	root = parse_pipe(prm);
	if (get_token_type(pick_next_token(prm)) != TK_EOF)
		return (NULL);
	return (root);
}

t_node	*parse_pipe(t_param *prm)
{
	t_node	*node;

	node = parse_exec(prm);
	if (get_token_type(pick_next_token(prm)) == TK_PIPE)
	{
		get_token(prm);
		node = make_pipe_node(prm, node, parse_pipe(prm));
	}
	return (node);
}

t_node	*parse_exec(t_param *prm)
{
	t_node	*node;
	t_token	peak_token;

	node = NULL;
	peak_token = get_token_type(pick_next_token(prm));
	if (is_redir(peak_token))
		node = parse_redir(prm);
	peak_token = get_token_type(pick_next_token(prm));
	while (peak_token == TK_WORD || is_redir(peak_token))
	{
		
		peak_token = get_token_type(pick_next_token(prm));
	}
	return (node);
}

/*il faut une fonction pour chaque truc de la grammaire. */