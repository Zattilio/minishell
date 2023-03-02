/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:13:44 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/02 16:17:05 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node	*make_node(t_param *prm, int id, int token_type, char *token)
{
	t_node	*node;

	if (token == NULL)
		return (NULL);
	node = ft_malloc_gc(prm, prm->source.id, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->id = id;
	node->token_type = token_type;
	node->token = token;
	return (node);
}

t_token	get_t_token_2(char *token)
{
	if (ft_strncmp(token, ">", 2) == 0)
		return (TK_SUP);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (TK_DINF);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (TK_DSUP);
	if (ft_strncmp(token, "$", 1) == 0)
		return (TK_DOLLAR);
	if (ft_strncmp(token, "\'", 1) == 0)
		return (TK_SQUOTE);
	if (ft_strncmp(token, "\"", 1) == 0)
		return (TK_DQUOTE);
	return (TK_WORD);
}

t_token	get_t_token(char *token)
{
	if (token == NULL)
		return (TK_ERROR);
	if (token[0] == '\0')
		return (TK_EOF);
	if (ft_strncmp(token, "|", 2) == 0)
		return (TK_PIPE);
	if (ft_strncmp(token, "<", 2) == 0)
		return (TK_INF);
	return (get_t_token_2(token));
}

size_t	test_double_token(t_param *prm, size_t cur)
{
	if (prm->source.line[cur + 1]
		&& ((prm->source.line[cur] == '<' && prm->source.line[cur + 1] == '<')
			|| (prm->source.line[cur] == '>'
				&& prm->source.line[cur + 1] == '>')))
		cur++;
	if (!ft_isspace(prm->source.line[cur]))
		cur++;
	return (cur);
}
