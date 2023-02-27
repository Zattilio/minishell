/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:48:44 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 16:32:19 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node	*make_node(t_param *prm, int id, int token_type, char *token)
{
	t_node	*node;

	node = ft_malloc_gc(prm, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->id = id;
	node->token_type = token_type;
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	get_token_type(char *token)
{
	if (ft_strncmp(token, "|", 1) == 0)
		return (TK_PIPE);
	if (ft_strncmp(token, "&", 1) == 0)
		return (TK_AMP);
	if (ft_strncmp(token, "<", 1) == 0)
		return (TK_INF);
	if (ft_strncmp(token, ">", 1) == 0)
		return (TK_SUP);
	if (ft_strncmp(token, "$", 1) == 0)
		return (TK_DOLLAR);
	if (ft_strncmp(token, "\'", 1) == 0)
		return (TK_SQUOTE);
	if (ft_strncmp(token, "\"", 1) == 0)
		return (TK_DQUOTE);
	if (ft_strncmp(token, "*", 1) == 0)
		return (TK_WILDCARD);
	return (TK_WORD);
}

t_node	*get_token(t_param *prm, int *id, char *line, int *cur)
{
	int		pos_start;
	char	*token;
	t_node	*node;

	if (!line)
		return (NULL);
	while (line[*cur] && ft_isspace(line[*cur]))
		(*cur)++;
	if (*cur >= (int)ft_strlen(line))
		return (NULL);
	pos_start = *cur;
	while (line[*cur] && !ft_isspace(line[*cur])
		&& !ft_strchr("|&<>$\'\"*", line[*cur]))
		(*cur)++;
	token = ft_substr_gc(prm, line, pos_start, *cur - pos_start + 1);
	node = make_node(prm, ++(*id), get_token_type(token), token);
	(*cur)++;
	return (node);
}
