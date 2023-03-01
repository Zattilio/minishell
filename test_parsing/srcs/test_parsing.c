/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:29:46 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/01 13:37:47 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv)
{
	t_param	prm;
	t_node	*node;
	char	*token;
	int		id;

	id = 0;
	if (argc != 2)
		return (1);
	ft_memset(&prm, 0, sizeof(t_param));
	prm.source.line = ft_strdup(argv[1]);
	prm.id = 1;
	if (prm.source.line)
		prm.source.line_size = ft_strlen(prm.source.line);
	while (1)
	{
		token = get_token(&prm);
		node = make_node(&prm, ++id, get_token_type(token), token);
		print_ast(node);
		if (node->token_type == TK_EOF)
			break ;
	}
	print_garbage(&prm);
	empty_garbage(&prm, prm.id);
	print_garbage(&prm);
	free(prm.source.line);
	return (0);
}
