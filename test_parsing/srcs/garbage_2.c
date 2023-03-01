/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:48:31 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/01 13:49:24 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*ft_malloc_gc(t_param *prm, size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		return (NULL);
	if (garbage_col(prm, result))
		return (NULL);
	return (result);
}

void	*ft_calloc_gc(t_param *prm, size_t nmemb, size_t size)
{
	void	*result;

	result = ft_calloc(nmemb, size);
	if (result == NULL)
		return (NULL);
	if (garbage_col(prm, result))
		return (NULL);
	return (result);
}
