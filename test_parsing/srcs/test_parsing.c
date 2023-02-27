/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:29:46 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 17:30:12 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(void)
{
	t_param	prm;

	t_node *token;
	int id = 0;
	int curseur = 0;
	char line[] = " <<a  && cou | bou || gfjg < >> o   ";
	
	ft_memset(&prm, 0, sizeof(t_param));
	token = get_token(&prm, &id, line, &curseur);
	while (token)
	{
		print_ast(token);
		token = get_token(&prm, &id, line, &curseur);
	}
	empty_garbage(&prm);
	return (0);
}
