/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:29:45 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/27 15:44:12 by mbocquel         ###   ########.fr       */
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

int	garbage_col(t_param *prm, void *ptr)
{
	t_garb	*new_garb;

	if (ptr == NULL)
		return ;
	new_garb = (t_garb *)malloc(sizeof(t_garb));
	if (new_garb == NULL)
		return (1);
	new_garb->ptr = ptr;
	new_garb->id = prm->id;
	new_garb->next = NULL;
	if (prm->garb == NULL)
		prm->garb = new_garb;
	else
	{
		new_garb->next = prm->garb;
		prm->garb = new_garb;
	}
	return (0);
}
