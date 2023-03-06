/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:31:33 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/06 17:00:31 by mbocquel         ###   ########.fr       */
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
/*il faur que je fasse en sorte de renoyer un node de type EXEC avec une 
commande "" si on m'envoie une chaine vide. */
t_node	*parsing(t_param *prm)
{
	t_node	*root;

	root = parse_pipe(prm);
	if (peek_tk(prm) != TK_EOF)
		return (NULL);
	prm->source.cur = 0;
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
	char	*arg;

	node = NULL;
	cmd = NULL;
	if (is_redir(peek_tk(prm)))
		node = parse_redir(prm);
	while (is_word(peek_tk(prm)) || is_redir(peek_tk(prm)))
	{
		if (is_word(peek_tk(prm)))
		{
			arg = get_word(prm);
			cmd = add_cmd_arg(prm, cmd, arg);
		}
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
	t_token	peek;
	char	*file_name;

	token = get_t_token(get_token(prm));
	file_name = NULL;
	peek = peek_tk(prm);
	if (!(peek == TK_WORD || peek == TK_SQUOTE
			|| peek == TK_DQUOTE || peek == TK_DOLLAR))
		return (NULL);
	if (token == TK_DINF)
		file_name = get_endheredoc(prm);
	else
		file_name = get_word(prm);
	node = make_redir_node(prm, NULL, token, file_name);
	return (node);
}

char	*get_endheredoc(t_param *prm)
{
	size_t	pos_end;
	char	*end_file;

	if (peek_tk(prm) == TK_SQUOTE)
	{
		get_token(prm);
		return (get_word_squote(prm));
	}
	if (peek_tk(prm) == TK_DQUOTE)
	{
		get_token(prm);
		if (get_pos_in_str(prm->source.line + prm->source.cur, '\"') == -1)
		{
			prm->source.error = ERR_DQUOTE_CLOSE;
			return (NULL);
		}
		pos_end = prm->source.cur + get_pos_in_str(prm->source.line + prm->source.cur, '\"');
		end_file = ft_substr_gc(prm, prm->source.line + prm->source.cur, 0, pos_end - prm->source.cur); 
		prm->source.cur = pos_end + 1;
		return (end_file);
	}
	else
	{
		pos_end = prm->source.cur + get_pos_in_str(prm->source.line + prm->source.cur, ' ');
		end_file = ft_substr_gc(prm, prm->source.line + prm->source.cur, 0, pos_end - prm->source.cur); 
		prm->source.cur = pos_end + 1;
		return (end_file);
	}
}
