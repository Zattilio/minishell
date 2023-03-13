/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:31:33 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/13 10:20:21 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*parse(t_param *prm, char *line)
{
	t_node	*root;
	char	*new_line;

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
	new_line = substitute_line(prm);
	if (check_error_parsing(prm) || peek_tk(prm) != TK_EOF)
	{
		g_return_value = 1;
		return (NULL);
	}
	ft_printf("new_line \n%s\n\n", new_line);
	prm->source.cur = 0;
	prm->source.error = 0;
	root = parse_pipe(prm);
	if (check_error_parsing(prm) || peek_tk(prm) != TK_EOF)
	{
		g_return_value = 1;
		return (NULL);
	}
	return (root);
}

t_node	*parse_pipe(t_param *prm)
{
	t_node	*node;

	if (!(is_redir(peek_tk(prm)) || is_word(peek_tk(prm))))
	{
		prm->source.error = ERR_PARSING;
		return (NULL);
	}
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
	{
		prm->source.error = ERR_PARSING;
		return (NULL);
	}
	if (token == TK_DINF)
		file_name = get_endheredoc(prm);
	else
		file_name = get_word(prm);
	if (file_name == NULL)
		prm->source.error = ERR_PARSING;
	node = make_redir_node(prm, NULL, token, file_name);
	return (node);
}

/*test du parser. je fait les substitutions avant 

char	*get_word_dquote(t_param *prm, t_bool sub)
{
	char	*word;

	word = NULL;
	while (!(peek_tk(prm) == TK_DQUOTE || peek_tk(prm) == TK_EOF))
	{
		word = ft_strjoin_gc(prm, prm->source.id, word, get_space(prm));
		if (peek_tk(prm) == TK_WORD_SUB && sub == TRUE)
			word = ft_strjoin_gc(prm, prm->source.id, word,
					substitute_word(prm, get_token(prm)));
		else
			word = ft_strjoin_gc(prm, prm->source.id, word, get_token(prm));
	}
	if (peek_tk(prm) == TK_EOF)
	{
		prm->source.error = ERR_DQUOTE_CLOSE;
		return (NULL);
	}
	word = ft_strjoin_gc(prm, prm->source.id, word, get_space(prm));
	get_token(prm);
	return (word);
}*/

char	*substitute_line(t_param *prm)
{
	char	*word;

	word = NULL;
	while (peek_tk(prm) != TK_EOF)
	{
		word = ft_strjoin_gc(prm, prm->source.id, word, get_space(prm));
		if (peek_tk(prm) == TK_WORD_SUB)
			word = ft_strjoin_gc(prm, prm->source.id, word,	substitute_word(prm, get_token(prm)));
		else if (peek_tk(prm) == TK_WORD || peek_tk(prm) == TK_PIPE)
			word = ft_strjoin_gc(prm, prm->source.id, word, get_token(prm));
		else if (peek_tk(prm) == TK_SQUOTE)
		{
			word = ft_strjoin_gc(prm, prm->source.id, word, get_token(prm));
			word = ft_strjoin_gc(prm, prm->source.id, word, get_word_squote(prm));
			word = ft_strjoin_gc(prm, prm->source.id, word, "\'");
		}
		else if (peek_tk(prm) == TK_DQUOTE)
		{
			word = ft_strjoin_gc(prm, prm->source.id, word, get_token(prm));
			word = ft_strjoin_gc(prm, prm->source.id, word, get_word_dquote(prm, FALSE));
			word = ft_strjoin_gc(prm, prm->source.id, word, "\"");
		}
		else if (peek_tk(prm) == TK_DSUP || peek_tk(prm) == TK_SUP || peek_tk(prm) == TK_INF)
		{
			word = ft_strjoin_gc(prm, prm->source.id, word, get_token(prm));
			word = ft_strjoin_gc(prm, prm->source.id, word, get_space(prm));
			if (peek_tk(prm) == TK_DQUOTE)
			{
				word = ft_strjoin_gc(prm, prm->source.id, word, get_token(prm));
				word = ft_strjoin_gc(prm, prm->source.id, word, get_word_dquote(prm, FALSE));
				word = ft_strjoin_gc(prm, prm->source.id, word, "\"");
			}
			else if (peek_tk(prm) == TK_SQUOTE)
			{
				word = ft_strjoin_gc(prm, prm->source.id, word, get_token(prm));
				word = ft_strjoin_gc(prm, prm->source.id, word, get_word_squote(prm));
				word = ft_strjoin_gc(prm, prm->source.id, word, "\'");
			}
			else
				word = ft_strjoin_gc(prm, prm->source.id, word, get_word(prm));
		}
		else if (peek_tk(prm) == TK_DINF)
		{
			word = ft_strjoin_gc(prm, prm->source.id, word, get_token(prm));
			word = ft_strjoin_gc(prm, prm->source.id, word, get_space(prm));
			word = ft_strjoin_gc(prm, prm->source.id, word, get_endheredoc(prm));
		}
		else
		{
			ft_printf_fd(2, "error dans le substitute line \n");
			break;
		}
	}
	return (word);
}
