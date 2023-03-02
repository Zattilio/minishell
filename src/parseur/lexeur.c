/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:48:44 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/02 15:05:06 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The lexer, or tokenizer aims to create groups of character from the command
line and identify what type they are. It does not check whether or not the 
command is synaxicaly correct (this is the role of the parser).*/

#include "parsing.h"

char	*get_token(t_param *prm)
{
	size_t	pos_start;
	char	*token;
	size_t	cur;

	cur = prm->source.cur;
	if (!prm->source.line)
		return (NULL);
	while (prm->source.line[cur] && ft_isspace(prm->source.line[cur]))
		cur++;
	if (cur >= prm->source.line_size)
		return (ft_strdup_gc(prm, ""));
	pos_start = cur;
	while (cur < prm->source.line_size && !ft_isspace(prm->source.line[cur])
		&& !ft_strchr(PARSING_STOPPER, prm->source.line[cur]))
	{	
		if (prm->source.line[cur + 1] && (ft_isspace(prm->source.line[cur + 1])
				|| ft_strchr(PARSING_STOPPER, prm->source.line[cur + 1])))
			break ;
		cur++;
	}
	cur = test_double_token(prm, cur);
	token = ft_substr_gc(prm, prm->source.line, pos_start, cur - pos_start);
	prm->source.cur = cur;
	return (token);
}

t_token	peek_tk(t_param *prm)
{
	int			pos_start;
	char		*token;
	size_t		cur;

	cur = prm->source.cur;
	if (!prm->source.line)
		return (TK_ERROR);
	while (prm->source.line[cur] && ft_isspace(prm->source.line[cur]))
		cur++;
	if (cur >= prm->source.line_size)
		return (TK_EOF);
	pos_start = cur;
	while (cur < prm->source.line_size && !ft_isspace(prm->source.line[cur])
		&& !ft_strchr(PARSING_STOPPER, prm->source.line[cur]))
	{
		if (prm->source.line[cur + 1] && (ft_isspace(prm->source.line[cur + 1])
				|| ft_strchr(PARSING_STOPPER, prm->source.line[cur + 1])))
			break ;
		cur++;
	}
	cur = test_double_token(prm, cur);
	token = ft_substr_gc(prm, prm->source.line, pos_start, cur - pos_start);
	return (get_t_token(token));
}
