/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:31:33 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/03 12:50:32 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The parser check that the syntax of the user command is valid. It then 
generates an Abstract Syntax Tree (AST) that will be use for the next step :
the execution.*/

/*Plusieurs approches de parsing ; Top Down Parsing et Bottom up parsing.
 mais aussi Recursive descent parser
 */

/* quand j'ai une erreur de syntax je renvoie un NULL, mais je l'interprete pas.
il faudra changer ca par la suite*/

#include "../parsing.h"

t_node	*parsing(t_param *prm)
{
	t_node	*root;

	root = parse_pipe(prm);
	if (peek_tk(prm) != TK_EOF)
		return (NULL);
	return (root);
}

t_node	*parse_pipe(t_param *prm)
{
	t_node	*node;

	node = parse_exec(prm);
	if (peek_tk(prm) == TK_PIPE)
	{
		get_token(prm);
		node = make_pipe_node(prm, node, parse_pipe(prm));
	}
	return (node);
}

t_node	*parse_exec(t_param *prm)
{
	t_node	*node;
	char	**cmd;

	node = NULL;
	cmd = NULL;
	if (is_redir(peek_tk(prm)))
		node = parse_redir(prm);
	while (peek_tk(prm) == TK_WORD || is_redir(peek_tk(prm)))
	{
		if (peek_tk(prm) == TK_WORD)
			cmd = add_cmd_arg(prm, cmd, get_token(prm));
		else
			add_last_left(&node, parse_redir(prm));
	}
	add_last_left(&node, make_exec_node(prm, cmd));
	return (node);
}

t_node	*parse_redir(t_param *prm)
{
	t_node	*node;
	t_token	token;
	char	*file_name;

	token = get_t_token(get_token(prm));
	file_name = NULL;
	if (!(peek_tk(prm) == TK_WORD || peek_tk(prm) == TK_SQUOTE
			|| peek_tk(prm) == TK_DQUOTE))
		return (NULL);
	file_name = get_word(prm);
	/*if (peek_tk(prm) == TK_WORD)
		file_name = get_token(prm);
	else if (peek_tk(prm) == TK_SQUOTE)
		file_name = get_word_squote(prm);
	else if (peek_tk(prm) == TK_DQUOTE)
		file_name = get_word_dquote(prm);*/
	node = make_redir_node(prm, NULL, token, file_name);
	return (node);
}
