/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:48:44 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 15:39:52 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node	*make_node(int id, int token_type, char *token)
{
	t_node	*node;

	node = ft_malloc(sizeof(t_node));
	node->id = id;
	node->token_type = token_type;
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*get_token(t_param *prm, int *id, char *line, int *cur)
{
	int 	pos_start;
	int 	pos_end;
	char	*token;

	if (!line)
		return (NULL);
	*id++;
	while (line[*cur] && ft_isspace(line[*cur]))
		*cur++;
	pos_start = *cur;
	while (line[*cur] && !ft_isspace(line[*cur]) && !ft_strchr("|&<>$\'\"*", line[*cur]))
		*cur++;
	pos_end = *cur;
	
}