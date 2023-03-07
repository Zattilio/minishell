/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:15:18 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/07 18:32:06 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	check_error_parsing(t_param *prm)
{
	if (prm->source.error == 0)
		return (0);
	if (prm->source.error == ERR_SQUOTE_CLOSE)
		ft_printf_fd(2,
			"minishell: parsing error: single quote not closed\n");
	else if (prm->source.error == ERR_DQUOTE_CLOSE)
		ft_printf_fd(2,
			"minishell: parsing error: double quote not closed\n");
	else if (prm->source.error == ERR_PARSING)
		ft_printf_fd(2,
			"minishell: parsing error\n");
	return (prm->source.error);
}
