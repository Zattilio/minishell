/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:57:00 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/03 15:20:01 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_redir(t_token token_type)
{
	if (token_type == TK_INF || token_type == TK_SUP
		|| token_type == TK_DINF || token_type == TK_DSUP)
		return (1);
	return (0);
}

int	is_word(t_token token_type)
{
	if (token_type == TK_WORD || token_type == TK_DOLLAR
		|| token_type == TK_SQUOTE || token_type == TK_DQUOTE)
		return (1);
	return (0);
}

void	print_space(int space)
{
	int	i;

	i = 15;
	while (i < space)
	{
		ft_printf(" ");
		i++;
	}
}

int	get_pos_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_nb_str(char **strs)
{
	int	i;

	i = 0;
	if (strs == NULL)
		return (0);
	while (strs[i])
		i++;
	return (i);
}
