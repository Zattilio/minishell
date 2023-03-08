/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:31:33 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 18:35:42 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node    *parse(t_param *prm, char *line)
{
    t_node    *root;

	if (prm->source.id != 0)
		empty_garbage(prm, prm->source.id);
	(prm->source.id)++;
	prm->source.line = line;
	garbage_col(prm, prm->source.id, line);
	prm->source.cur = 0;
	prm->source.error = 0;
	prm->source.line_size = ft_strlen(line);
	if (peek_tk(prm) == TK_EOF)
		return (NULL);
	root = parse_pipe(prm);
	if (check_error_parsing(prm) || peek_tk(prm) != TK_EOF)
		return (NULL);
	return (root);
}

/*old ==> a ne plus utiliser*/
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
	if (prm->source.cur == 0 && peek_tk(prm) == TK_EOF)
		return (make_exec_node(prm, add_cmd_arg(prm, cmd, "")));
	if (is_redir(peek_tk(prm)))
		node = parse_redir(prm);
	while (is_word(peek_tk(prm)) || is_redir(peek_tk(prm)))
	{
		if (is_word(peek_tk(prm)))
		{
			arg = get_word(prm);
			if (arg == NULL)
				return (NULL);
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
			|| peek == TK_DQUOTE || peek == TK_WORD_SUB))
		return (NULL);
	if (token == TK_DINF)
		file_name = get_endheredoc(prm);
	else
		file_name = get_word(prm);
	node = make_redir_node(prm, NULL, token, file_name);
	return (node);
}
