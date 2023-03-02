/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:31:33 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/02 15:12:51 by mbocquel         ###   ########.fr       */
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

#include "parsing.h"

t_node	*make_pipe_node(t_param *prm, t_node *left, t_node *right)
{
	t_node	*node;

	node = ft_malloc_gc(prm, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->id = prm->source.id;
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
	node->id = prm->source.id;
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
	node->id = prm->source.id;
	node->token_type = TK_EXEC;
	node->token = get_tk_str(TK_EXEC);
	node->cmd = cmd;
	return (node);
}

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

void	add_last_left(t_node **root, t_node *node)
{
	t_node	*elem;

	elem = *root;
	if (elem == NULL)
		*root = node;
	else
	{
		while (elem->left)
			elem = elem->left;
		elem->left = node;
	}
}

int	get_nb_arg(char **cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (0);
	while (cmd[i])
		i++;
	return (i);
}

char	**add_cmd_arg(t_param *prm, char **cmd, char *arg)
{
	char	**new_cmd;
	int		nb_arg;
	int		i;

	i = -1;
	nb_arg = get_nb_arg(cmd);
	new_cmd = (char **)ft_malloc_gc(prm, (nb_arg + 2) * sizeof(char *));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd[nb_arg] = ft_strdup_gc(prm, arg);
	if (new_cmd[nb_arg] == NULL)
		return (NULL);
	new_cmd[nb_arg + 1] = NULL;
	while (++i < nb_arg)
		new_cmd[i] = cmd[i];
	return (new_cmd);
}

char	*get_word(t_param *prm)
{
	t_token peek;
	char	*token;

	peek = peek_tk(prm);
	if (!(peek == TK_WORD || peek == TK_SQUOTE))
		return (NULL);
	token = get_token(prm);
	if (get_t_token(token) == TK_WORD)
		return (token);
	//if (get_t_token(token) == TK_SQUOTE)
	else
		return (get_word_squote(prm));
}

char	*get_word_squote(t_param *prm)
{
	char 	*word;
	size_t	pos_start;
	
	word = NULL;
	pos_start = prm->source.cur;
	while (peek_tk(prm) != TK_SQUOTE && peek_tk(prm) != TK_EOF)
		get_token(prm);
	if (peek_tk(prm) == TK_EOF)
	{
		prm->source.error = ERR_SQUOTE_CLOSE;
		return (NULL);
	}
	word = ft_substr_gc(prm, prm->source.line, pos_start, prm->source.cur - pos_start);
	return (word);
}
