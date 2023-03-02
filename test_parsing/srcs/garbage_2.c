/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:48:31 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/02 12:08:50 by mbocquel         ###   ########.fr       */
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

char	*ft_strjoin_gc(t_param *prm, char const *s1, char const *s2)
{
	char	*result_join;
	int		i;
	int		len[2];

	len[0] = 0;
	len[1] = 0;
	if (s1)
		len[0] = ft_strlen(s1);
	if (s2)
		len[1] = ft_strlen(s2);
	result_join = ft_calloc_gc(prm, (len[0] + len[1] + 1), sizeof(char));
	if (result_join == NULL)
		return (NULL);
	i = 0;
	while (i < len[0])
	{
		result_join[i] = s1[i];
		i++;
	}
	while (i < len[0] + len[1])
	{
		result_join[i] = s2[i - len[0]];
		i++;
	}
	return (result_join);
}
