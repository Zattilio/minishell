/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:29:45 by mbocquel          #+#    #+#             */
/*   Updated: 2023/02/28 16:14:56 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*We created two fonctions malloc_gabage_collection and calloc_gc. They are
able to reproduce the behaviour of malloc and calloc but they also store the
allocated adresse in out garbage list. This way we don't have to worry about 
free until we are finish.*/

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

void	empty_garbage(t_param *prm)
{
	t_garb	*elem_garb;
	t_garb	*temp;

	elem_garb = prm->garb;
	while (elem_garb)
	{
		temp = elem_garb;
		free(elem_garb->ptr);
		elem_garb = temp->next;
		free(temp);
	}
}

void	remove_from_garb(t_param *prm, void *ptr)
{
	t_garb	*elem;
	t_garb	*next;
	t_garb	*previous;

	previous = NULL;
	elem = prm->garb;
	while (elem && elem->ptr != ptr)
	{
		previous = elem;
		elem = elem->next;
	}
	if (elem)
	{
		previous->next = elem->next;
		free(elem->ptr);
		free(elem);
	}
}
