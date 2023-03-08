/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlanza <jlanza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:15:18 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/08 12:57:05 by jlanza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
